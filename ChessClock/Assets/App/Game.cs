using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace App
{
    public class Game : MonoBehaviour
    {
        public ClockButton LeftButton;
        public ClockButton RightButton;
        public Timer LeftTimer;
        public Timer RightTimer;
        public PlayPause PlayPause;
        public bool LeftIsWhite;
        public bool WhiteMove;
        public GameObject WinnerPrefab;
        public GameObject LoserPrefab;

        private ClockButton _whiteButton, _blackButton;
        public Timer _whiteTimer, _blackTimer;

        void Start()
        {
            LeftButton.Interactive = false;
            RightButton.Interactive = false;
            _whiteButton = LeftButton;
            _blackButton = RightButton;
            _whiteTimer =  LeftTimer;
            _blackTimer = RightTimer;

            //Lichess.LichessApi api = new Lichess.LichessApi();
            //Debug.Log(api.GetMyInfo());
        }

        public void PlayPlausedPressed()
        {
            if (PlayPause.State == EGameState.Paused)
            {
                PlayPause.State = EGameState.Running;
                _whiteButton.Interactive = WhiteMove;
                _blackButton.Interactive = !WhiteMove;
                _whiteTimer.Running = WhiteMove;
                _blackTimer.Running = !WhiteMove;
            }
            else
            {
                PlayPause.State = EGameState.Paused;
                LeftButton.Interactive = false;
                RightButton.Interactive = false;
                _whiteTimer.Running = _blackTimer.Running = false;
            }
        }

        public void LeftPressed()
        {
            ChangeSides();
        }

        public void RightPressed()
        {
            ChangeSides();
        }

        void ChangeSides()
        {
            if (LeftIsWhite && WhiteMove)
            {
                _whiteButton.Interactive = false;
                _blackButton.Interactive = true;
                _whiteTimer.Running = false;
                _blackTimer.Running = true;
                WhiteMove = false;

                return;
            }

            _whiteButton.Interactive = true;
            _blackButton.Interactive = false;
            _whiteTimer.Running = true;
            _blackTimer.Running = false;
            WhiteMove = true;
        }

        void Update()
        {
            if (PlayPause.State == EGameState.Running)
            {
                _whiteTimer.Step(Time.deltaTime);
                _blackTimer.Step(Time.deltaTime);
            }
        }
    }
}
