namespace UIWidgets
{
	using UIWidgets.l10n;

	/// <summary>
	/// AutoComboboxIcons.
	/// </summary>
	public partial class AutoComboboxIcons : AutoCombobox<ListViewIconsItemDescription, ListViewIcons, ListViewIconsItemComponent, AutocompleteIcons, ComboboxIcons>
	{
		/// <inheritdoc/>
		protected override string GetStringValue(ListViewIconsItemDescription item)
		{
			return item.LocalizedName ?? Localization.GetTranslation(item.Name);
		}
	}
}