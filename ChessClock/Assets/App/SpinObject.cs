using UnityEngine;

public class SpinObject : MonoBehaviour
{
    public float Speed = 1;
    public bool RandomStart = false;

    private void Start()
    {
        if (RandomStart)
            transform.rotation = Random.rotation;
    }

    void Update()
    {
        transform.Rotate(Vector3.up, Time.deltaTime*Speed);
    }
}
