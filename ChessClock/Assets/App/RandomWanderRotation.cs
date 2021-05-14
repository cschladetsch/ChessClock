using UnityEngine;

namespace App
{
    public class RandomWanderLocation : MonoBehaviour
    {
        public float Speed;

        private Camera _camera;

        void Start()
        {
            _camera = Camera.main;
        }
    }
}
