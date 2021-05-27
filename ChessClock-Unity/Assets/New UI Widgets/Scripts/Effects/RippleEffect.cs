namespace UIWidgets
{
	using System;
	using System.Collections.Generic;
	using UnityEngine;
	using UnityEngine.EventSystems;
	using UnityEngine.Serialization;
	using UnityEngine.UI;

	/// <summary>
	/// Ripple effect.
	/// </summary>
	[RequireComponent(typeof(RectTransform))]
	[RequireComponent(typeof(Graphic))]
	[AddComponentMenu("UI/New UI Widgets/Effects/Ripple Effect")]
	public class RippleEffect : MonoBehaviour, IPointerDownHandler, IPointerUpHandler, IPointerClickHandler, IMaterialModifier, IMeshModifier
	{
		/// <summary>
		/// IDs of ripple shader properties.
		/// </summary>
		protected struct RippleShaderIDs : IEquatable<RippleShaderIDs>
		{
			/// <summary>
			/// Start color ID.
			/// </summary>
			public readonly int StartColor;

			/// <summary>
			/// End color ID.
			/// </summary>
			public readonly int EndColor;

			/// <summary>
			/// Speed ID.
			/// </summary>
			public readonly int Speed;

			/// <summary>
			/// Max size ID.
			/// </summary>
			public readonly int MaxSize;

			/// <summary>
			/// Count ID.
			/// </summary>
			public readonly int Count;

			/// <summary>
			/// Ripple ID.
			/// </summary>
			public readonly int Ripple;

			private RippleShaderIDs(int startColor, int endColor, int speed, int maxSize, int count, int ripple)
			{
				StartColor = startColor;
				EndColor = endColor;
				Speed = speed;
				MaxSize = maxSize;
				Count = count;
				Ripple = ripple;
			}

			/// <summary>
			/// Get RippleShaderIDs instance.
			/// </summary>
			public static RippleShaderIDs Instance
			{
				get
				{
					return new RippleShaderIDs(
						Shader.PropertyToID("_RippleStartColor"),
						Shader.PropertyToID("_RippleEndColor"),
						Shader.PropertyToID("_RippleSpeed"),
						Shader.PropertyToID("_RippleMaxSize"),
						Shader.PropertyToID("_RippleCount"),
						Shader.PropertyToID("_Ripple"));
				}
			}

			/// <summary>
			/// Determines whether the specified object is equal to the current object.
			/// </summary>
			/// <param name="obj">The object to compare with the current object.</param>
			/// <returns>true if the specified object is equal to the current object; otherwise, false.</returns>
			public override bool Equals(object obj)
			{
				if (obj is RippleShaderIDs)
				{
					return Equals((RippleShaderIDs)obj);
				}

				return false;
			}

			/// <summary>
			/// Determines whether the specified object is equal to the current object.
			/// </summary>
			/// <param name="other">The object to compare with the current object.</param>
			/// <returns>true if the specified object is equal to the current object; otherwise, false.</returns>
			public bool Equals(RippleShaderIDs other)
			{
				return StartColor == other.StartColor && EndColor == other.EndColor && Speed == other.Speed && MaxSize == other.MaxSize && Count == other.Count && Ripple == other.Ripple;
			}

			/// <summary>
			/// Hash function.
			/// </summary>
			/// <returns>A hash code for the current object.</returns>
			public override int GetHashCode()
			{
				return StartColor ^ EndColor ^ Speed ^ MaxSize ^ Count ^ Ripple;
			}

			/// <summary>
			/// Compare specified instances.
			/// </summary>
			/// <param name="left">Left instance.</param>
			/// <param name="right">Right instances.</param>
			/// <returns>true if the instances are equal; otherwise, false.</returns>
			public static bool operator ==(RippleShaderIDs left, RippleShaderIDs right)
			{
				return left.Equals(right);
			}

			/// <summary>
			/// Compare specified instances.
			/// </summary>
			/// <param name="left">Left instance.</param>
			/// <param name="right">Right instances.</param>
			/// <returns>true if the instances are now equal; otherwise, false.</returns>
			public static bool operator !=(RippleShaderIDs left, RippleShaderIDs right)
			{
				return !left.Equals(right);
			}
		}

		/// <summary>
		/// Ripple shader.
		/// </summary>
		[SerializeField]
		protected Shader RippleShader;

		[SerializeField]
		[FormerlySerializedAs("color")]
		Color startColor = Color.white;

		/// <summary>
		/// Start color of the ripple.
		/// </summary>
		public Color StartColor
		{
			get
			{
				return startColor;
			}

			set
			{
				startColor = value;
				UpdateMaterial();
			}
		}

		[SerializeField]
		Color endColor = Color.white;

		/// <summary>
		/// End color of the ripple.
		/// </summary>
		public Color EndColor
		{
			get
			{
				return endColor;
			}

			set
			{
				endColor = value;
				UpdateMaterial();
			}
		}

		[SerializeField]
		float speed = 0.5f;

		/// <summary>
		/// Ripple speed.
		/// </summary>
		public float Speed
		{
			get
			{
				return speed;
			}

			set
			{
				speed = value;
				UpdateMaterial();
			}
		}

		[SerializeField]
		[Range(0f, 1f)]
		float maxSize = 1f;

		/// <summary>
		/// Ripple size.
		/// </summary>
		public float MaxSize
		{
			get
			{
				return maxSize;
			}

			set
			{
				maxSize = value;
				UpdateMaterial();
			}
		}

		/// <summary>
		/// Base material.
		/// </summary>
		[NonSerialized]
		protected Material BaseMaterial;

		/// <summary>
		/// Ripple material.
		/// </summary>
		[NonSerialized]
		protected Material RippleMaterial;

		[NonSerialized]
		Graphic graphic;

		/// <summary>
		/// Graphic component.
		/// </summary>
		protected Graphic Graphic
		{
			get
			{
				if (graphic == null)
				{
					graphic = GetComponent<Graphic>();
				}

				return graphic;
			}
		}

		/// <summary>
		/// Ripples data.
		/// </summary>
		[NonSerialized]
		protected List<float> RipplesData;

		[NonSerialized]
		RectTransform rectTransform;

		/// <summary>
		/// RectTransform component.
		/// </summary>
		protected RectTransform RectTransform
		{
			get
			{
				if (rectTransform == null)
				{
					rectTransform = transform as RectTransform;
				}

				return rectTransform;
			}
		}

		/// <summary>
		/// Max ripples count.
		/// </summary>
		protected static int MaxRipples = 10;

		/// <summary>
		/// Float values per ripple.
		/// </summary>
		protected static int FloatPerRipple = 3;

		/// <summary>
		/// Ripple shader ids.
		/// </summary>
		protected static RippleShaderIDs ShaderIDs = RippleShaderIDs.Instance;

		/// <summary>
		/// Remove oldest and dead ripples.
		/// </summary>
		protected void CleanRipples()
		{
			// remove oldest ripple
			if (RipplesData.Count > ((MaxRipples - 1) * FloatPerRipple))
			{
				RipplesData.RemoveRange(0, FloatPerRipple);
			}

			// remove dead ripples
			var died = UtilitiesTime.GetTime(false) - (MaxSize / Speed);
			var start = RipplesData.Count - FloatPerRipple;
			for (var i = start; i >= 0; i -= FloatPerRipple)
			{
				if (RipplesData[i + 2] < died)
				{
					RipplesData.RemoveRange(i, FloatPerRipple);
				}
			}
		}

		/// <summary>
		/// Add ripple.
		/// </summary>
		/// <param name="eventData">Event data.</param>
		protected virtual void AddRipple(PointerEventData eventData)
		{
			CleanRipples();

			var size = RectTransform.rect.size;
			var aspect_ratio = size.x / size.y;

			var pivot = RectTransform.pivot;

			Vector2 current_point;
			RectTransformUtility.ScreenPointToLocalPointInRectangle(RectTransform, eventData.position, eventData.pressEventCamera, out current_point);
			current_point.x += size.x * pivot.x;
			current_point.y -= size.y * (1f - pivot.y);

			var center_x = current_point.x / size.x;
			var center_y = (1f + (current_point.y / size.y)) / aspect_ratio;

			RipplesData.Add(center_x);
			RipplesData.Add(center_y);
			RipplesData.Add(UtilitiesTime.GetTime(false));

			if (RippleMaterial != null)
			{
				RippleMaterial.SetInt(ShaderIDs.Count, RipplesData.Count / FloatPerRipple);
				RippleMaterial.SetFloatArray(ShaderIDs.Ripple, RipplesData);
				Graphic.SetMaterialDirty();
			}
		}

		/// <summary>
		/// Process pointer click event.
		/// </summary>
		/// <param name="eventData">Event data.</param>
		public virtual void OnPointerClick(PointerEventData eventData)
		{
			AddRipple(eventData);
		}

		/// <summary>
		/// Process pointer down event.
		/// </summary>
		/// <param name="eventData">Event data.</param>
		public virtual void OnPointerDown(PointerEventData eventData)
		{
		}

		/// <summary>
		/// Process pointer up event.
		/// </summary>
		/// <param name="eventData">Event data.</param>
		public virtual void OnPointerUp(PointerEventData eventData)
		{
		}

		/// <summary>
		/// Modify mesh.
		/// </summary>
		/// <param name="mesh">Mesh.</param>
		public virtual void ModifyMesh(Mesh mesh)
		{
		}

		/// <summary>
		/// Add uv1 to the mesh.
		/// </summary>
		/// <param name="verts">Vertex helper.</param>
		public virtual void ModifyMesh(VertexHelper verts)
		{
			var vertex = default(UIVertex);

			// get min and max position to calculate uv1
			verts.PopulateUIVertex(ref vertex, 0);
			var min_x = vertex.position.x;
			var max_x = min_x;
			var min_y = vertex.position.y;
			var max_y = min_y;

			for (int i = 1; i < verts.currentVertCount; i++)
			{
				verts.PopulateUIVertex(ref vertex, i);

				min_x = Math.Min(min_x, vertex.position.x);
				max_x = Math.Max(max_x, vertex.position.x);

				min_y = Math.Min(min_y, vertex.position.y);
				max_y = Math.Max(max_y, vertex.position.y);
			}

			// set uv1 for the ripple shader
			var width = max_x - min_x;
			var height = max_y - min_y;
			var size = RectTransform.rect.size;
			var aspect_ratio = size.x / size.y;

			for (int i = 0; i < verts.currentVertCount; i++)
			{
				verts.PopulateUIVertex(ref vertex, i);

				vertex.uv1 = new Vector2(
					(vertex.position.x - min_x) / width,
					(vertex.position.y - min_y) / height / aspect_ratio);

				verts.SetUIVertex(vertex, i);
			}
		}

		/// <summary>
		/// Init material.
		/// </summary>
		protected void InitMaterial()
		{
			var n = MaxRipples * FloatPerRipple;
			if (RipplesData == null)
			{
				RipplesData = new List<float>(n);
			}

			for (int i = RipplesData.Count; i < n; i++)
			{
				RipplesData.Add(-2);
			}

			SetMaterialProperties();
		}

		/// <summary>
		/// Set material properties.
		/// </summary>
		protected void SetMaterialProperties()
		{
			if (RippleMaterial != null)
			{
				RippleMaterial.SetColor(ShaderIDs.StartColor, startColor);
				RippleMaterial.SetColor(ShaderIDs.EndColor, endColor);
				RippleMaterial.SetFloat(ShaderIDs.Speed, speed);
				RippleMaterial.SetFloat(ShaderIDs.MaxSize, maxSize);
				RippleMaterial.SetInt(ShaderIDs.Count, RipplesData.Count / FloatPerRipple);
				RippleMaterial.SetFloatArray(ShaderIDs.Ripple, RipplesData);
			}
		}

		/// <summary>
		/// Update material.
		/// </summary>
		protected void UpdateMaterial()
		{
			SetMaterialProperties();

			if (RippleMaterial != null)
			{
				Graphic.SetMaterialDirty();
			}
		}

		/// <summary>
		/// Get modified material.
		/// </summary>
		/// <param name="baseMaterial">Base material.</param>
		/// <returns>Modified material.</returns>
		public virtual Material GetModifiedMaterial(Material baseMaterial)
		{
			if ((BaseMaterial != null) && (baseMaterial.GetInstanceID() == BaseMaterial.GetInstanceID()))
			{
				return RippleMaterial;
			}

			if (RippleMaterial != null)
			{
#if UNITY_EDITOR
				DestroyImmediate(RippleMaterial);
#else
				Destroy(RippleMaterial);
#endif
			}

			BaseMaterial = baseMaterial;
			RippleMaterial = new Material(baseMaterial)
			{
				shader = RippleShader,
			};
			InitMaterial();

			return RippleMaterial;
		}
	}
}