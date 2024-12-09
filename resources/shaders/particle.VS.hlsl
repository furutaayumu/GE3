#include "particle.hlsli"

struct TransformationMatrix
{
    float4x4 WVP;
    float32_t4x4 World;
};

StructuredBuffer<TransformationMatrix> gTransformationMatrices:register(t0);



struct VertexShaderInput {
	float4 position : POSITION0;
    float2 texcoord : TEXCOORD0;
};

VertexShaderOutput main(VertexShaderInput input, uint32_t instancedId : SV_InstanceID) {
	VertexShaderOutput output;
	output.position = mul(input.position, gTransformationMatrices[instancedId].WVP) ;//output.position = input.position
    output.texcoord = input.texcoord;
	
	return output;
}


