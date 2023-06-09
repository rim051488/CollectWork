struct VSInput {
	float3 pos:POSITION;//座標
	float3 norm:NORMAL;//法線
	float4 diff:COLOR0;//ディフューズカラー
	float4 spec:COLOR1;//スペキュラカラー
	float4 uv0:TEXCOORD0;//テクスチャ座標
	float4 uv1:TEXCOORD1;//サブテクスチャ座標
};

struct VSOutput {
	float4 pos:POSITION0;
	float4 lpos:POSITION1;
	float3 norm:NORMAL;
	float4 uv:TEXCOORD;
	float4 diff:COLOR0;
	float4 spec:COLOR1;
	float4 svpos:SV_POSITION;
};

// 基本パラメータ
struct CONST_BUFFER_BASE
{
	float4 AntiViewportMat[4]; // アンチビューポート行列
	float4 ProjMat[4]; // ビュー　→　プロジェクション行列
	float4 ViewMat[3]; // ワールド　→　ビュー行列
	float4 LocalWorldMat[3]; // ローカル　→　ワールド行列

	float4 ToonOutLineSize; // トゥーンの輪郭線の大きさ
	float DiffuseSource; // ディフューズカラー( 0.0f:マテリアル  1.0f:頂点 )
	float SpecularSource; // スペキュラカラー(   0.0f:マテリアル  1.0f:頂点 )
	float MulSpecularColor; // スペキュラカラー値に乗算する値( スペキュラ無効処理で使用 )
	float Padding;
};

// その他の行列
struct CONST_BUFFER_OTHERMAT
{
	float4 ShadowMapLightViewProjectionMatrix[3][4]; // シャドウマップ用のライトビュー行列とライト射影行列を乗算したもの
	float4 TextureMatrix[3][2]; // テクスチャ座標操作用行列
};

// 基本パラメータ
cbuffer BUFFER_BASE : register(b1)
{
	CONST_BUFFER_BASE g_Base;
};

// その他の行列
cbuffer BUFFER_OTHERMAT : register(b2)
{
	CONST_BUFFER_OTHERMAT g_OtherMat;
};

VSOutput main(VSInput input)
{
	VSOutput output;
	float4 pos = float4(input.pos, 1);
	float4 WorldPos;
	float4 ViewPos;

	// ローカル座標をワールド座標にする
	//WorldPos.xyz = mul(pos, g_Base.LocalWorldMat);
	//WorldPos.w = 1.0f;

	WorldPos.x = dot(pos, g_Base.LocalWorldMat[0]);
	WorldPos.y = dot(pos, g_Base.LocalWorldMat[1]);
	WorldPos.z = dot(pos, g_Base.LocalWorldMat[2]);
	WorldPos.w = 1.0f;

	// ワールド座標をビュー行列にする
	//ViewPos.xyz = mul(WorldPos, g_Base.ViewMat);
	//ViewPos.w = 1.0f;

	ViewPos.x = dot(WorldPos, g_Base.ViewMat[0]);
	ViewPos.y = dot(WorldPos, g_Base.ViewMat[1]);
	ViewPos.z = dot(WorldPos, g_Base.ViewMat[2]);
	ViewPos.w = 1.0f;

	// ローカル座標をワールド座標にする
	//output.svpos = mul(ViewPos, g_Base.ProjMat);

	output.svpos.x = dot(ViewPos, g_Base.ProjMat[0]);
	output.svpos.y = dot(ViewPos, g_Base.ProjMat[1]);
	output.svpos.z = dot(ViewPos, g_Base.ProjMat[2]);
	output.svpos.w = dot(ViewPos, g_Base.ProjMat[3]);

	// 従法線、接線、法線をビューベクトルに変換
	float3 WorldNrm;
	float3 ViewNrm;

	WorldNrm.x = dot(input.norm, g_Base.LocalWorldMat[0].xyz);
	WorldNrm.y = dot(input.norm, g_Base.LocalWorldMat[1].xyz);
	WorldNrm.z = dot(input.norm, g_Base.LocalWorldMat[2].xyz);

	ViewNrm.x = dot(WorldNrm, g_Base.ViewMat[0].xyz);
	ViewNrm.y = dot(WorldNrm, g_Base.ViewMat[1].xyz);
	ViewNrm.z = dot(WorldNrm, g_Base.ViewMat[2].xyz);

	output.uv.x = dot(input.uv0, g_OtherMat.TextureMatrix[0][0]);
	output.uv.y = dot(input.uv0, g_OtherMat.TextureMatrix[0][1]);

	output.pos = ViewPos;
	output.norm = ViewNrm;

	return output;
}