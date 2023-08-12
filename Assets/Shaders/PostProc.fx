cbuffer PostProcBuffer : register(b0)
{
    int mode;
    float param0;
    float param1;
    float param2;
}

Texture2D textureMap0 : register(t0);
Texture2D textureMap1 : register(t1);
Texture2D textureMap2 : register(t2);
Texture2D textureMap3 : register(t3);

SamplerState textureSampler : register(s0);

struct VS_INPUT
{
    float3 position : POSITION;
    float2 texCoord : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 position : SV_Position;
    float2 texCoord : TEXCOORD;
};

VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    output.position = float4(input.position, 1.0f);
    output.texCoord = input.texCoord;
    return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
    float4 finalColor = { 0.f, 0.f, 0.f, 1.f};
    if (mode == 0) // none
    {
        finalColor = textureMap0.Sample(textureSampler, input.texCoord);
    }
    else if (mode == 1) // Monochrome
    {
        float4 screenColor = textureMap0.Sample(textureSampler, input.texCoord);
        float c = (screenColor.r + screenColor.g + screenColor.b) / 3.0f;
        float4 greyscale = float4(c, c, c, screenColor.a);
        float4 colorCast = { param0, param1, param2, 1.0f };
        finalColor = greyscale * colorCast;

    }
    else if (mode == 2) // Invert
    {
        finalColor = 1.0f - textureMap0.Sample(textureSampler, input.texCoord);
    }
    else if (mode == 3) // Mirror
    {
        float2 texCoord = input.texCoord;
        texCoord.x = texCoord.x * param0;
        texCoord.y = texCoord.y * param1;
        finalColor = textureMap0.Sample(textureSampler, texCoord);
    }
    else if (mode == 4) // Blur
    {
        float u = input.texCoord.x;
        float v = input.texCoord.y;
        
        finalColor = textureMap0.Sample(textureSampler, float2(u, v)) +
        textureMap0.Sample(textureSampler, float2(u + param0, v)) +
        textureMap0.Sample(textureSampler, float2(u - param0, v)) +
        textureMap0.Sample(textureSampler, float2(u, v + param1)) +
        textureMap0.Sample(textureSampler, float2(u, v - param1)) +
        textureMap0.Sample(textureSampler, float2(u + param0, v + param1)) +
        textureMap0.Sample(textureSampler, float2(u + param0, v - param1)) +
        textureMap0.Sample(textureSampler, float2(u - param0, v + param1)) +
        textureMap0.Sample(textureSampler, float2(u - param0, v - param1));
        finalColor *= 0.12f;
    }
    else if (mode == 5) // Combine2
    {
        float4 color0 = textureMap0.Sample(textureSampler, input.texCoord);
        float4 color1 = textureMap1.Sample(textureSampler, input.texCoord);
        finalColor = (color0 + color1) * 0.5f;
    }
    else if (mode == 6) // Motion Blur
    {
        //float u = input.texCoord.x;
        //float v = input.texCoord.y;
        //finalColor = textureMap0.Sample(textureSampler, float2(u, v)) +
        //textureMap0.Sample(textureSampler, float2(u + param0, v)) +
        //textureMap0.Sample(textureSampler, float2(u - param0, v)) +
        //textureMap0.Sample(textureSampler, float2(u, v + param1)) +
        //textureMap0.Sample(textureSampler, float2(u, v - param1)) +
        //textureMap0.Sample(textureSampler, float2(u + param0, v + param1)) +
        //textureMap0.Sample(textureSampler, float2(u + param0, v - param1)) +
        //textureMap0.Sample(textureSampler, float2(u - param0, v + param1)) +
        //textureMap0.Sample(textureSampler, float2(u - param0, v - param1));
        //finalColor *= 0.12f;
    }
    else if (mode == 7) // Chromatic Aberration
    {
        float2 distortion = float2(param0, -param0);
        
        float4 redChannel = textureMap0.Sample(textureSampler, input.texCoord + distortion.x * input.texCoord);
        float4 greenChannel = textureMap0.Sample(textureSampler, input.texCoord);
        float4 blueChannel = textureMap0.Sample(textureSampler, input.texCoord + distortion.y * input.texCoord);
        
        finalColor = float4(redChannel.r, greenChannel.g, blueChannel.b, 1.0f);
    }
    return finalColor;
}