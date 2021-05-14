namespace UIWidgets
{
	using UIWidgets.Styles;
	using UnityEngine;
	using UnityEngine.EventSystems;

	/// <summary>
	/// Base class for the AutoCombobox widget.
	/// </summary>
	/// <typeparam name="TItem">Item type.</typeparam>
	/// <typeparam name="TListView">ListView type.</typeparam>
	/// <typeparam name="TListViewComponent">ListView.DefaultItem type.</typeparam>
	/// <typeparam name="TAutocomplete">Autocomplete type.</typeparam>
	/// <typeparam name="TCombobox">Combobox type.</typeparam>
	public abstract class AutoCombobox<TItem, TListView, TListViewComponent, TAutocomplete, TCombobox> : MonoBehaviour, IStylable
		where TListView : ListViewCustom<TListViewComponent, TItem>
		where TListViewComponent : ListViewItem
		where TAutocomplete : AutocompleteCustom<TItem, TListViewComponent, TListView>
		where TCombobox : ComboboxCustom<TListView, TListViewComponent, TItem>
	{
		/// <summary>
		/// Autocomplete.
		/// </summary>
		[SerializeField]
		public TAutocomplete Autocomplete;

		/// <summary>
		/// Combobox.
		/// </summary>
		[SerializeField]
		public TCombobox Combobox;

		/// <summary>
		/// Autocomplete input listener.
		/// </summary>
		protected DeselectListener AutocompleteInputListener;

		bool isInited;

		/// <summary>
		/// Start this instance.
		/// </summary>
		protected virtual void Start()
		{
			Init();
		}

		/// <summary>
		/// Init this instance.
		/// </summary>
		public virtual void Init()
		{
			if (isInited)
			{
				return;
			}

			isInited = true;

			Autocomplete.Init();
			Autocomplete.OnOptionSelectedItem.AddListener(OnOptionSelected);

			Combobox.Init();
			Combobox.ListView.OnSelectObject.AddListener(OnSelect);
			Combobox.OnCurrentClick.AddListener(AutocompleteShow);
			Combobox.ListView.OnDataSourceChanged.AddListener(ListViewDataSourceChanged);

			AutocompleteInputListener = Utilities.GetOrAddComponent<DeselectListener>(Autocomplete.InputFieldAdapter);
			AutocompleteInputListener.Deselect.AddListener(AutocompleteHide);

			Autocomplete.DataSource = Combobox.ListView.DataSource.ListReference();

			AutocompleteHide();
		}

		/// <summary>
		/// Process DataSource changed event.
		/// </summary>
		/// <param name="listView">ListView.</param>
		protected virtual void ListViewDataSourceChanged(ListViewCustom<TListViewComponent, TItem> listView)
		{
			Autocomplete.DataSource = listView.DataSource.ListReference();
		}

		/// <summary>
		/// Process the destroy event.
		/// </summary>
		protected virtual void OnDestroy()
		{
			Autocomplete.OnOptionSelectedItem.RemoveListener(OnOptionSelected);
			Combobox.ListView.OnSelectObject.RemoveListener(OnSelect);
			Combobox.OnCurrentClick.RemoveListener(AutocompleteShow);
			Combobox.ListView.OnDataSourceChanged.RemoveListener(ListViewDataSourceChanged);

			if (AutocompleteInputListener != null)
			{
				AutocompleteInputListener.Deselect.RemoveListener(AutocompleteHide);
			}
		}

		/// <summary>
		/// Process selected option.
		/// </summary>
		/// <param name="item">Item.</param>
		protected virtual void OnOptionSelected(TItem item)
		{
			var index = Combobox.ListView.DataSource.IndexOf(item);
			Combobox.ListView.Select(index);

			AutocompleteHide();
		}

		/// <summary>
		/// Process the select event.
		/// </summary>
		/// <param name="index">Index.</param>
		protected virtual void OnSelect(int index)
		{
			Autocomplete.InputFieldAdapter.text = GetStringValue(Combobox.ListView.DataSource[index]);
		}

		/// <summary>
		/// Convert item to string.
		/// </summary>
		/// <returns>The string value.</returns>
		/// <param name="item">Item.</param>
		protected abstract string GetStringValue(TItem item);

		/// <summary>
		/// Has selected item?
		/// </summary>
		/// <returns>true if ListView has selected item; otherwise false.</returns>
		protected bool HasSelected()
		{
			return Combobox.ListView.SelectedIndex >= 0;
		}

		/// <summary>
		/// Show autocomplete.
		/// </summary>
		/// <param name="index">Index.</param>
		/// <param name="item">Item.</param>
		protected virtual void AutocompleteShow(int index, TItem item)
		{
			AutocompleteShow();
		}

		/// <summary>
		/// Show autocomplete.
		/// </summary>
		protected virtual void AutocompleteShow()
		{
			if (HasSelected())
			{
				Autocomplete.InputFieldAdapter.text = GetStringValue(Combobox.ListView.SelectedItem);
			}
			
			Autocomplete.gameObject.SetActive(true);
			Combobox.HideCurrent();

			if (!EventSystem.current.alreadySelecting)
			{
				EventSystem.current.SetSelectedGameObject(Autocomplete.InputFieldAdapter.gameObject);
			}
		}

		/// <summary>
		/// Hide autocomplete.
		/// </summary>
		protected virtual void AutocompleteHide()
		{
			if (HasSelected())
			{
				Autocomplete.gameObject.SetActive(false);
				Combobox.ShowCurrent();
			}
			else
			{
				AutocompleteShow();
			}
		}

		/// <inheritdoc/>
		public virtual bool SetStyle(Style style)
		{
			Autocomplete.SetStyle(style);
			Combobox.SetStyle(style);

			return true;
		}

		/// <inheritdoc/>
		public virtual bool GetStyle(Style style)
		{
			Autocomplete.GetStyle(style);
			Combobox.GetStyle(style);

			return true;
		}
	}
}