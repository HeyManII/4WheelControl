using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class DHT : MonoBehaviour
{
    InputController sen;
    public float hum;
    public float tem;

    // Start is called before the first frame update
    void Start()
    {
        sen = new InputController();
        sen.Begin("10.68.69.99", 80);
    }

    // Update is called once per frame
    void Update()
    {

    }

    void OnGUI()
    {
        var hum = sen.Currenth;
        var tem = sen.Currentt;
        Debug.Log(hum);
        Debug.Log(tem);
        GUI.Label(new Rect(0, 0, 150, 20), "Temperature: " + tem.ToString() + "C");
        GUI.Label(new Rect(0, 15, 100, 20), "Humidity: " + hum.ToString() + "%");
    }
}
