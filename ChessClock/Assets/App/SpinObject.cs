using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpinObject : MonoBehaviour
{
    public float Speed = 1;

    void Update()
    {
        transform.Rotate(Vector3.up, Time.deltaTime*Speed);
    }
}
