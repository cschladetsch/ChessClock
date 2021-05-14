using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

namespace App
{
    public class ClockButton : MonoBehaviour
    {
        public bool Interactive
        {
            get { return _button.interactable; }
            set { _button.interactable = value; }
        }

        private Button _button;

        void Start()
        {
            _button = GetComponent<Button>();
        }

        void Update()
        {
        }
    }
}
