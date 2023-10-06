using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LED : MonoBehaviour
{	
	OutputController outLED;

    // Start is called before the first frame update
    void Start()
    {
        outLED = new OutputController();
        outLED.Begin("10.66.89.91", 80);
    }

    // Update is called once per frame
    void Update()
    {
    	if (Input.GetKeyDown(KeyCode.UpArrow))
    	{
    		outLED.sendblue();
    	}
    	if (Input.GetKeyUp(KeyCode.B))
    	{
    		outLED.sendblue();
    	}

    	if (Input.GetKeyDown(KeyCode.G))
    	{
    		outLED.sendgreen();
    	}
    	if (Input.GetKeyUp(KeyCode.G))
    	{
    		outLED.sendgreen();
    	}

    	if (Input.GetKeyDown(KeyCode.R))
    	{
    		outLED.sendred();
    	}
    	if (Input.GetKeyUp(KeyCode.R))
    	{
    		outLED.sendred();
    	}
    }
}
