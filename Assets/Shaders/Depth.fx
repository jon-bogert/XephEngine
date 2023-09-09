cbuffer TransformBuffer : register(b0)
{
    matrix wvp;
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
    float4 objectNDCPosition : TEXCOORD0;
};

VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    output.position = mul(float4(input.position, 1.0f), wvp);
    output.objectNDCPosition = mul(float4(input.position, 1.0f), wvp);
    return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
    float depth = (1.0f - input.objectNDCPosition.z / input.objectNDCPosition.w) * 10;
    return float4(depth, depth, depth, 1.0f);
}