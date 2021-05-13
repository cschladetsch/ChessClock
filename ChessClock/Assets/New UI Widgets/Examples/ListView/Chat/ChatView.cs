﻿namespace UIWidgets.Examples
{
	using System;
	using UIWidgets;
	using UnityEngine;
	using UnityEngine.Events;

	/// <summary>
	/// ChatView.
	/// </summary>
	public class ChatView : ListViewCustomHeight<ChatLineComponent, ChatLine>
	{
		/// <summary>
		/// Chat event.
		/// </summary>
		[SerializeField]
		public UnityEvent MyEvent;

		#region DataSource wrapper and Filter

		ObservableList<ChatLine> fullDataSource;

		/// <summary>
		/// All messages.
		/// </summary>
		public ObservableList<ChatLine> FullDataSource
		{
			get
			{
				return fullDataSource;
			}

			set
			{
				if (fullDataSource != null)
				{
					// unsubscribe update event
					fullDataSource.OnChange -= UpdateDataSource;
				}

				fullDataSource = value;

				if (fullDataSource != null)
				{
					// subscribe update event
					fullDataSource.OnChange += UpdateDataSource;
				}

				UpdateDataSource();
			}
		}

		Func<ChatLine, bool> filter;

		/// <summary>
		/// Messages filter.
		/// </summary>
		public Func<ChatLine, bool> Filter
		{
			get
			{
				return filter;
			}

			set
			{
				filter = value;
				UpdateDataSource();
			}
		}

		void UpdateDataSource()
		{
			DataSource.BeginUpdate();
			DataSource.Clear();
			if (filter != null)
			{
				foreach (var item in FullDataSource)
				{
					if (Filter(item))
					{
						DataSource.Add(item);
					}
				}
			}
			else
			{
				DataSource.AddRange(FullDataSource);
			}

			DataSource.EndUpdate();
		}

		bool isInited;

		/// <summary>
		/// Init this instance.
		/// </summary>
		public override void Init()
		{
			if (isInited)
			{
				return;
			}

			isInited = true;

			base.Init();

			if (fullDataSource == null)
			{
				fullDataSource = new ObservableList<ChatLine>();
				fullDataSource.AddRange(DataSource);
				fullDataSource.OnChange += UpdateDataSource;

				UpdateDataSource();
			}
		}
		#endregion

		/// <summary>
		/// Process the destroy event.
		/// </summary>
		protected override void OnDestroy()
		{
			if (fullDataSource != null)
			{
				fullDataSource.OnChange -= UpdateDataSource;
			}

			base.OnDestroy();
		}
	}
}