// Description: Cel shader that does transform.

cbuffer TransformBuffer : register(b0)
{
    matrix world;
    matrix wvp;
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

cbuffer SettingBuffer : register(b3)
{
    bool useDiffuseMap;
}

Texture2D diffuseMap : register(t0);

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
};

VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
	
    matrix toWorld = world;
    matrix toNDC = wvp;
    float3 localPosition = input.position;
	
    output.position = mul(float4(localPosition, 1.0f), toNDC);
    output.worldNormal = mul(input.normal, (float3x3) toWorld);
    output.worldTangent = mul(input.tangent, (float3x3) toWorld);
    output.dirToLight = -lightDirection;
    output.dirToView = normalize(viewPosition - mul(float4(localPosition, 1.0f), toWorld).xyz);
    output.texCoord = input.texCoord;
    return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
    float3 n = normalize(input.worldNormal);
    float3 light = normalize(input.dirToLight);
    float3 view = normalize(input.dirToView);
	
	// ambient color
    float4 ambient = lightAmbient * materialAmbient;
	
	//diffuse color
    float d = saturate(dot(light, n));
    float dIntensity = smoothstep(0.005f, 0.01f, d);
    float4 diffuse = dIntensity * lightDiffuse * materialDiffuse;
	
	//specular color
    float3 r = reflect(-light, n);
    float base = saturate(dot(r, view));
    float s = pow(base, materialPower); // specular intensity
    float sIntensity = smoothstep(0.005f, 0.01f, s);
    float4 specular = sIntensity * lightSpecular * materialSpecular;
	
	//Colors from texture
    float4 diffuseMapColor = (useDiffuseMap) ? diffuseMap.Sample(textureSampler, input.texCoord) : 1.0f;
	
	//Combine Colors
    float4 finalColor = (ambient + diffuse + materialEmissive) * diffuseMapColor + specular;
    return finalColor;
}