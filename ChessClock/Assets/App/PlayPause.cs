using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

namespace App
{
    public enum EGameState
    {
        None,
        Paused,
        WhiteMove,
        BlackMove,
        Running,
    }

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
                    case EGameState.WhiteMove:
                        Text.text = "White";
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
