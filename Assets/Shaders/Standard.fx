// Description: Simple shader that does transform.

cbuffer TransformBuffer : register(b0)
{
	matrix world;
	matrix wvp;
	matrix lwvp;
	float3 viewPosition;
}

cbuffer LightBuffer : register(b1)
{
    float4 lightAmbient;
    float4 lightDiffuse;
    float4 lightSpecular;
    float3 lightDirection;
}

cbuffer MaterialBuffer : register(b2)
{
	float4 materialAmbient;
	float4 materialDiffuse;
	float4 materialSpecular;
	float4 materialEmissive;
	float materialPower;
	float materialNormalIntensity;
}

cbuffer SettingBuffer : register (b3)
{
	bool useDiffuseMap;
	bool useNormalMap;
    bool useDisplMap;
    float displWeight;
    bool useSpecMap;
    bool useShadowMap;
}

Texture2D diffuseMap : register(t0);
Texture2D normalMap : register(t1);
Texture2D displMap : register(t2);
Texture2D specMap : register(t3);
Texture2D shadowMap : register(t4);

SamplerState textureSampler : register(s0);

struct VS_INPUT
{
    float3 position : POSITION;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float2 texCoord : TEXCOORD;
};

struct VS_OUTPUT
{
	float4 position : SV_Position;
	float3 worldNormal : NORMAL;
	float3 worldTangent : TANGENT;
	float3 dirToLight : TEXCOORD0;
	float3 dirToView : TEXCOORD1;
    float2 texCoord : TEXCOORD2;
    float4 lightNDCPosition : TEXCOORD3;
};

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output;
	
	matrix toWorld = world;
	matrix toNDC = wvp;
	float3 localPosition = input.position;
	if (useDisplMap)
    {
        float displColor = (2.0f * displMap.SampleLevel(textureSampler, input.texCoord, 0.0f).r) - 1.0f;
        localPosition += (input.normal * displColor * displWeight);
    }
	
	output.position = mul(float4(localPosition, 1.0f), toNDC);
	output.worldNormal = mul(input.normal, (float3x3) toWorld);
	output.worldTangent = mul(input.tangent, (float3x3) toWorld);
	output.dirToLight = -lightDirection;
	output.dirToView = normalize(viewPosition - mul(float4(localPosition, 1.0f), toWorld).xyz); 
	output.texCoord = input.texCoord;
	if (useShadowMap)
    {
        output.lightNDCPosition = mul(float4(localPosition, 1.0f), lwvp);
    }
	return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
	float3 n = normalize(input.worldNormal);
	float3 light = normalize(input.dirToLight);
	float3 view = normalize(input.dirToView);
	
	// set up normal from map
	if(useNormalMap)
	{
		float3 t = normalize(input.worldTangent);
		float3 b = normalize(cross(n, t));
		float3x3 tbnw  = float3x3(t, b, n);// coords from map to world space
		float4 normalMapColor = normalMap.Sample(textureSampler, input.texCoord);
		float3 unpackedNormalMap = normalize(float3((normalMapColor.xy * 2.0f) - 1.0f, normalMapColor.z));
		n = normalize(lerp(n, normalize(mul(unpackedNormalMap, tbnw)), materialNormalIntensity));
	}
	
	// ambient color
	float4 ambient = lightAmbient * materialAmbient;
	
	//diffuse color
	float d = saturate(dot(light, n));
	float4 diffuse = d * lightDiffuse * materialDiffuse;
	
	//specular color
	float3 r = reflect(-light, n);
	float base = saturate(dot(r, view));
	float s = pow(base, materialPower); // specular intensity
	float4 specular = s * lightSpecular * materialSpecular;
	
	//Colors from texture
    float4 diffuseMapColor =  (useDiffuseMap) ? diffuseMap.Sample(textureSampler, input.texCoord) : 1.0f;
    float4 specMapColor = (useSpecMap) ? specMap.Sample(textureSampler, input.texCoord) : 1.0f;
	
	//Combine Colors
    float4 finalColor = (ambient + diffuse + materialEmissive) * diffuseMapColor + (specular * specMapColor.r);
	
    if (useShadowMap)
    {
        float actualDepth = 1.0f - (input.lightNDCPosition.z / input.lightNDCPosition.w);
        float2 shadowUV = input.lightNDCPosition.xy / input.lightNDCPosition.w;
        float u = (shadowUV.x + 1.0f) * 0.5f;
        float v = 1.0 - (shadowUV.y + 1.0f) * 0.5f;
        if (saturate(u) == u && saturate(v) == v)
        {
            float4 savedColor = shadowMap.Sample(textureSampler, float2(u, v));
            float savedDepth = savedColor.r;
			if (savedDepth > actualDepth)
            {
                finalColor = (ambient + materialEmissive) * diffuseMapColor;
            }
        }
    }
	return finalColor;
}