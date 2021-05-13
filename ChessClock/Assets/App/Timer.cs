using UnityEngine;
using TMPro;
using System;

namespace App
{
    public class Timer : MonoBehaviour
    {
        public float InitialTimeMinutes;
        public float Increment;
        public bool Running;
        public TextMeshProUGUI Text;
        public TextMeshProUGUI Millis;

        private TimeSpan _current;

        void Start()
        {
            Reset();
        }

        public void Reset()
        {
            _current = TimeSpan.FromMinutes(InitialTimeMinutes);
            UpdateText();
        }

        public void Step(float delta)
        {
            if (!Running)
                return;

            _current = _current.Subtract(TimeSpan.FromSeconds(delta));
            UpdateText();
        }

        string GetSub(float num)
        {
            return string.Format("{0:00}", num);
        }
        private void UpdateText()
        {
            Text.text = $"0:{GetSub(_current.Minutes)}:{GetSub(_current.Seconds)}";
            Millis.text = $"{GetSub(_current.Milliseconds/10)}";
        }
    }
}
