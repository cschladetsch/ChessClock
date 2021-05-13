﻿namespace UIWidgets
{
	using UnityEngine;

	/// <summary>
	/// ComboboxIcons item component.
	/// Demonstrate how to remove selected item - add Remove() call on Button.OnClick().
	/// </summary>
	public class ComboboxIconsItemComponent : ListViewIconsItemComponent
	{
		/// <summary>
		/// ComboboxIcons.
		/// </summary>
		public ComboboxIcons ComboboxIcons;

		/// <summary>
		/// Remove this instance.
		/// </summary>
		public void Remove()
		{
			ComboboxIcons.ListView.Deselect(Index);
		}
	}
}