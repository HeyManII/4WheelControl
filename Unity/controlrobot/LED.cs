using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LED : MonoBehaviour
{	
	OutputController outLED;
    public string ips;

    // Start is called before the first frame update
    void Start()
    {
        outLED = new OutputController();
        outLED.Begin(ips, 80);
    }

    // Update is called once per frame
    void Update()
    {
    	if (Input.GetKeyDown(KeyCode.UpArrow))
    	{
    		outLED.sendfront();
    	}
    	if (Input.GetKeyUp(KeyCode.UpArrow))
    	{
    		outLED.sendfront();
    	}

    	if (Input.GetKeyDown(KeyCode.DownArrow))
    	{
    		outLED.sendback();
    	}
    	if (Input.GetKeyUp(KeyCode.DownArrow))
    	{
    		outLED.sendback();
    	}

    	if (Input.GetKeyDown(KeyCode.LeftArrow))
    	{
    		outLED.sendleft();
    	}
    	if (Input.GetKeyUp(KeyCode.LeftArrow))
    	{
    		outLED.sendleft();
    	}

        if (Input.GetKeyDown(KeyCode.RightArrow))
        {
            outLED.sendright();
        }
        if (Input.GetKeyUp(KeyCode.RightArrow))
        {
            outLED.sendright();
        }
    }
}
