cbuffer TransformBuffer : register(b0)
{
    matrix wvp;
}

Texture2D textureMap0 : register(t0);
SamplerState textureSampler : register(s0);

cbuffer SettingsBuffer : register(b1)
{
    float sampleRadius;
    bool useSSAO;
}

struct VS_INPUT
{
    float3 position : POSITION;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float3 texCoord : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 position : SV_Position;
    float3 normal : NORMAL;
};

#define KERNEL_SIZE 16
float3 sampleKernel[KERNEL_SIZE];

VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    output.position = mul(float4(input.position, 1.0f), wvp);
    output.normal = input.normal;
    return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
    float2 uv = input.position.xy / input.position.w;
    uv = uv * 0.5 + 0.5;

    float depth = textureMap0.Sample(textureSampler, uv).r;
    float ao;
    
    for (int i = 0; i < KERNEL_SIZE; i++)
    {
        float3 sample = float3(uv, depth) + sampleKernel[i] * sampleRadius;
        
        // Convert sample point to clip space
        float4 offset = float4(sample, 1.0);
        offset = mul(offset, wvp);
        
        // Get the depth at the sample point
        float sampleDepth = textureMap0.Sample(textureSampler, offset.xy).r;
        
        // Compare the sample depth to the original point's depth
        float rangeCheck = smoothstep(0.02, 0.03, sampleRadius / abs(depth - sampleDepth));
        ao += (depth > sampleDepth ? 1.0 : 0.0) * rangeCheck;
    }

    ao = 1.0 - (ao / float(KERNEL_SIZE));
    
    return float4(ao, ao, ao, 1.0f);
    //return float4(depth, depth, depth, 1.0f);
}