// Upgrade NOTE: replaced 'mul(UNITY_MATRIX_MVP,*)' with 'UnityObjectToClipPos(*)'

// Flare in the sprite space with sprite transparency support.
// Flare support sprite texture transparency and displayed only on opaque parts.
// Should be used only _Flare* properties
// other properties should have the default value to be compatible with Unity UI.

Shader "Custom/New UI Widgets/UIFlareTransparent"
{
	Properties
	{
		// Sprite texture
		[PerRendererData] _MainTex("Sprite Texture", 2D) = "white" {}
		// Tint
		_Color("Tint", Color) = (1,1,1,1)
		// flare color
		_FlareColor("Flare Color", Color) = (1,1,1,1)
		// flare size in fraction of texture size
		_FlareSize("Flare Size", Float) = 0.2
		// flare speed
		_FlareSpeed("Flare Speed", Float) = 0.2
		// flare delay in seconds
		_FlareDelay("Flare Delay", Float) = 0.0

		_StencilComp("Stencil Comparison", Float) = 8
		_Stencil("Stencil ID", Float) = 0
		_StencilOp("Stencil Operation", Float) = 0
		_StencilWriteMask("Stencil Write Mask", Float) = 255
		_StencilReadMask("Stencil Read Mask", Float) = 255

		_ColorMask("Color Mask", Float) = 15
	}

	SubShader
	{
		Tags
		{
			"Queue" = "Transparent"
			"IgnoreProjector" = "True"
			"RenderType" = "Transparent"
			"PreviewType" = "Plane"
			"CanUseSpriteAtlas" = "True"
		}

		Stencil
		{
			Ref[_Stencil]
			Comp[_StencilComp]
			Pass[_StencilOp]
			ReadMask[_StencilReadMask]
			WriteMask[_StencilWriteMask]
		}

		Cull Off
		Lighting Off
		ZWrite Off
		ZTest[unity_GUIZTestMode]
		Fog{ Mode Off }
		Blend SrcAlpha OneMinusSrcAlpha
		ColorMask[_ColorMask]

		Pass
		{
		CGPROGRAM
			#pragma vertex vert
			#pragma fragment frag
			#include "UnityCG.cginc"
			#include "UIWidgets.cginc"

			struct appdata_t
			{
				float4 vertex   : POSITION;
				float4 color    : COLOR;
				float2 texcoord : TEXCOORD0;
			};

			struct v2f
			{
				float4 vertex   : SV_POSITION;
				fixed4 color    : COLOR;
				half2 texcoord  : TEXCOORD0;
			};

			fixed4 _Color;
			float4 _FlareColor;
			float _FlareSize;
			float _FlareSpeed;
			float _FlareDelay;

			v2f vert(appdata_t IN)
			{
				v2f OUT;
				OUT.vertex = UnityObjectToClipPos(IN.vertex);
				OUT.texcoord = IN.texcoord;
				#ifdef UNITY_HALF_TEXEL_OFFSET
				OUT.vertex.xy += (_ScreenParams.zw - 1.0) * float2(-1,1);
				#endif
				OUT.color = IN.color * _Color;
				return OUT;
			}

			sampler2D _MainTex;

			float flare_distance(float center, float size, float pos, float delay)
			{
				float half_size = size / 2.0;
				float left = center - half_size;
				float right = center + half_size;
				if ((left < 0) && (pos > (left + delay)))
				{
					pos -= delay;
				}
				else if ((right > 1.0) && (pos < (right - delay)))
				{
					pos += delay;
				}

				return abs(smoothstep(left, right, pos) - 0.5) * 2.0;
			}

			fixed4 frag(v2f IN) : SV_Target
			{
				float delay = 1.0 + (_FlareDelay * _FlareSpeed);
				float flare_center = frac(_Time.y * (_FlareSpeed / delay)) * delay;
				float rate = flare_distance(flare_center, _FlareSize, IN.texcoord.x, delay);

				float4 base_color = tex2D(_MainTex, IN.texcoord);
				float4 color = base_color * IN.color;
				float3 flare_temp = lerp(color.rgb, _FlareColor.rgb, _FlareColor.a);
				float4 flare = float4(flare_temp.r, flare_temp.g, flare_temp.b, 1);

				#if defined(UIWIDGETS_COLORSPACE_GAMMA) || defined(UNITY_COLORSPACE_GAMMA)
				color.rgb = lerp(flare.rgb, color.rgb, rate);
				#else
				color.rgb = lerp(LinearToGammaSpace4(flare).rgb, color.rgb, rate);
				color = GammaToLinearSpace4(color);
				#endif

				clip(color.a - 0.01);

				return color;
			}
		ENDCG
		}
	}
}
