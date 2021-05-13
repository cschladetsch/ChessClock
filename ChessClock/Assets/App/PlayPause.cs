using UnityEngine;
using TMPro;

namespace App
{
    public class PlayPause : MonoBehaviour
    {
        public TextMeshProUGUI Text;

        public EGameState State
        {
            set
            {
                switch (value)
                {
                    case EGameState.Paused:
                        Text.text = "Paused";
                        break;
                    case EGameState.Running:
                        Text.text = "Running";
                        break;
                }
                _state = value;
            }

            get { return _state; }
        }

        private EGameState _state;

        void Start()
        {
            State = EGameState.Paused;
        }
    }
}
