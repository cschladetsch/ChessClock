using UnityEngine;
using TMPro;

namespace App
{
    public class PlayPauseButton : MonoBehaviour
    {
        public TextMeshProUGUI Text;

        public EGameState State
        {
            set
            {
                switch (value)
                {
                    case EGameState.Paused:
                        Text.text = "Play";
                        break;
                    case EGameState.Running:
                        Text.text = "Pause";
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
