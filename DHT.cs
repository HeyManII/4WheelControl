using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DHT : MonoBehaviour
{
    InputController sen;
    public float hum;

    // Start is called before the first frame update
    void Start()
    {
        sen = new InputController();
        sen.Begin("10.66.197.192", 80);
    }

    // Update is called once per frame
    void Update()
    {
        var hum = sen.CurrentValue;
        Debug.Log(hum);
    }

    void OnGUI()
    {
        GUI.Label(new Rect(0, 0, 100, 20), "Temperature: "+ hum +"C");
        GUI.Label(new Rect(0, 15, 100, 20), "Humidity: "+"%");
    }
}
