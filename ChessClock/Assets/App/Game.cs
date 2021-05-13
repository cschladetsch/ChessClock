using System;
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
        public SpinObject SpinCamera;
        public TimeSpan TotalTime;
        public TimeSpan Increment;
        public float SpinGain = 2;

        public Timer _whiteTimer, _blackTimer;

        private ClockButton _whiteButton, _blackButton;
        private bool _paused = true;

        void Start()
        {
            SpinCamera = Camera.main.GetComponent<SpinObject>();
            LeftButton.Interactive = false;
            RightButton.Interactive = false;
            _whiteButton = LeftButton;
            _blackButton = RightButton;
            _whiteTimer =  LeftTimer;
            _blackTimer = RightTimer;
            SetSpinSpeed(0);

            _whiteTimer.InitialTime = _blackTimer.InitialTime = TimeSpan.FromMinutes(1);

            _whiteTimer.Reset();
            _blackTimer.Reset();

            TotalTime = LeftTimer.Remaining + RightTimer.Remaining;
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

            _paused = !_paused;
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
            var white = true;
            if (LeftIsWhite && WhiteMove)
                white = false;
            
            var black = !white;

            _whiteButton.Interactive = white;
            _blackButton.Interactive = black;
            _whiteTimer.Running = white;
            _blackTimer.Running = black;
            WhiteMove = white;
        }

        void Update()
        {
            if (_paused)
                return;

            if (PlayPause.State == EGameState.Running)
            {
                _whiteTimer.Step(Time.deltaTime);
                _blackTimer.Step(Time.deltaTime);
            }

            double speed;
            if (WhiteMove)
                speed = -SpinGain*_whiteTimer.Remaining.TotalMilliseconds/_whiteTimer.InitialTime.TotalMilliseconds;
            else
                speed = SpinGain*_blackTimer.Remaining.TotalMilliseconds/_blackTimer.InitialTime.TotalMilliseconds;

            SetSpinSpeed(speed*SpinGain);
        }

        private void SetSpinSpeed(double speed)
        {
            SpinCamera.Speed = (float)speed;
        }
    }
}
