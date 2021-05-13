using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class FrameRateDisplay : MonoBehaviour
{
    public TextMeshProUGUI Text;

    float _lastTest;
    float _frames;

    private void Start()
    {
        Text.text = "";
    }

    void Update()
    {
        ++_frames;
        var now = Time.time;
        if (now - _lastTest < 1)
        {
            return;
        }
        var delta = now - _lastTest;
        _lastTest = now;
        var fps = _frames/delta;
        _frames = 0;

        Text.text = $"{(int)fps}fps";
    }
}
