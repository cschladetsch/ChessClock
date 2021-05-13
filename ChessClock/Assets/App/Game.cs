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
        public GameObject SetupObject;

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
                SetupObject.SetActive(false);
            }
            else
            {
                SetupObject.SetActive(true);
                PlayPause.State = EGameState.Paused;
                LeftButton.Interactive = false;
                RightButton.Interactive = false;
                _whiteTimer.Running = _blackTimer.Running = false;
            }

            _paused = !_paused;

            if (_paused)
                SpinCamera.Speed = 0;
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

        Timer CurrentTimer() => WhiteMove ? _whiteTimer : _blackTimer;

        void Update()
        {
            if (_paused)
                return;

            UpdateTimers();

            MoveBackground();
        }

        private void UpdateTimers()
        {
            if (PlayPause.State == EGameState.Running)
            {
                _whiteTimer.Step(Time.deltaTime);
                _blackTimer.Step(Time.deltaTime);
            }
        }
        
        private void MoveBackground()
        {
            var timer = CurrentTimer();
            var alpha = timer.Remaining.TotalSeconds/timer.InitialTime.TotalSeconds;
            if (WhiteMove)
                alpha *= -1;
            SetSpinSpeed(alpha*SpinGain);
        }

        private void SetSpinSpeed(double speed)
        {
            SpinCamera.Speed = (float)speed;
        }
    }
}
