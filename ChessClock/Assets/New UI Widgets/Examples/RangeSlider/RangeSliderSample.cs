namespace UIWidgets.Examples
{
	using UIWidgets;
	using UnityEngine;
	using UnityEngine.UI;

	/// <summary>
	/// How to use RangeSlider.
	/// </summary>
	[RequireComponent(typeof(RangeSlider))]
	public class RangeSliderSample : MonoBehaviour, IUpgradeable
	{
		/// <summary>
		/// Text component to display RangeSlider values.
		/// </summary>
		[SerializeField]
		[HideInInspector]
		[System.Obsolete("Replaced with TextAdapter.")]
		protected Text Text;

		/// <summary>
		/// Text component to display RangeSlider values.
		/// </summary>
		[SerializeField]
		protected TextAdapter TextAdapter;

		RangeSlider slider;

		/// <summary>
		/// Adds listeners.
		/// </summary>
		protected virtual void Start()
		{
			slider = GetComponent<RangeSlider>();
			if (slider != null)
			{
				slider.OnValuesChange.AddListener(SliderChanged);
				SliderChanged(slider.ValueMin, slider.ValueMax);
			}
		}

		/// <summary>
		/// Handle changed values.
		/// </summary>
		/// <param name="min">Min value.</param>
		/// <param name="max">Max value.</param>
		protected virtual void SliderChanged(int min, int max)
		{
			if (TextAdapter != null)
			{
				if (slider.WholeNumberOfSteps)
				{
					TextAdapter.text = string.Format("Range: {0:000} - {1:000}; Step: {2}", min, max, slider.Step);
				}
				else
				{
					TextAdapter.text = string.Format("Range: {0:000} - {1:000}", min, max);
				}
			}
		}

		/// <summary>
		/// Remove listeners.
		/// </summary>
		protected virtual void OnDestroy()
		{
			if (slider != null)
			{
				slider.OnValuesChange.RemoveListener(SliderChanged);
			}
		}

		/// <summary>
		/// Upgrade this instance.
		/// </summary>
		public virtual void Upgrade()
		{
#pragma warning disable 0612, 0618
			Utilities.GetOrAddComponent(Text, ref TextAdapter);
#pragma warning restore 0612, 0618
		}

#if UNITY_EDITOR
		/// <summary>
		/// Validate this instance.
		/// </summary>
		protected virtual void OnValidate()
		{
			Compatibility.Upgrade(this);
		}
#endif
	}
}