using UnityEngine;
using TMPro;
using System;

namespace App
{
    public class Timer : MonoBehaviour
    {
        public TimeSpan InitialTime;
        public float Increment;
        public bool Running;
        public TextMeshProUGUI Text;
        public TextMeshProUGUI Millis;
        public TimeSpan Remaining;

        void Start()
        {
            Reset();
        }

        public void Reset()
        {
            Remaining = InitialTime;
            UpdateText();
        }

        public void Step(float delta)
        {
            if (!Running)
                return;

            Remaining = Remaining.Subtract(TimeSpan.FromSeconds(delta));

            UpdateText();
        }

        private string FormatDigits(float num)
            => string.Format("{0:00}", num);

        private void UpdateText()
        {
            Text.text = $"{FormatDigits(Remaining.Minutes)}:{FormatDigits(Remaining.Seconds)}";
            Millis.text = $"{FormatDigits(Remaining.Milliseconds/10)}";
        }
    }
}
