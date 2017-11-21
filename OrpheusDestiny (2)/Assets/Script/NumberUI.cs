using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine;

public class NumberUI {

    private static NumberUI instance = null;
    public static NumberUI Instance
    {
        get
        {
            if (instance == null)
                instance = new NumberUI();

            return instance;
        }
    }
    private NumberUI()
    {

    }

    public void UIUpdate(Image Thousand, Image Hundred, Image Ten, Image One, int Init)
    {
        int Temp = Init;

        if (Thousand != null)
        { 
        SetImage(Thousand, Init / 1000);
            Temp = Init % 1000;
        }

        if (Hundred != null)
        { 
            SetImage(Hundred, Temp / 100);
            Temp = Temp % 100;
        }
        if (Ten != null)
        {
            SetImage(Ten, (Temp / 10));
            Temp = Temp % 10;
        }
        SetImage(One, Temp);
        Temp = Init;
    }


    void SetImage(Image Empty, int inum)
    {
        switch (inum)
        {
            case 1:
                Empty.GetComponent<Image>().sprite = Resources.Load("Number1",typeof(Sprite)) as Sprite;
                break;
            case 2:
                Empty.GetComponent<Image>().sprite = Resources.Load("Number2", typeof(Sprite)) as Sprite;
                break;
            case 3:
                Empty.GetComponent<Image>().sprite = Resources.Load("Number3", typeof(Sprite)) as Sprite;
                break;
            case 4:
                Empty.GetComponent<Image>().sprite = Resources.Load("Number4", typeof(Sprite)) as Sprite;
                break;
            case 5:
                Empty.GetComponent<Image>().sprite = Resources.Load("Number5", typeof(Sprite)) as Sprite;
                break;
            case 6:
                Empty.GetComponent<Image>().sprite = Resources.Load("Number6", typeof(Sprite)) as Sprite;
                break;
            case 7:
                Empty.GetComponent<Image>().sprite = Resources.Load("Number7", typeof(Sprite)) as Sprite;
                break;
            case 8:
                Empty.GetComponent<Image>().sprite = Resources.Load("Number8", typeof(Sprite)) as Sprite;
                break;
            case 9:
                Empty.GetComponent<Image>().sprite = Resources.Load("Number9", typeof(Sprite)) as Sprite;
                break;
            case 0:
                Empty.GetComponent<Image>().sprite = Resources.Load("Number0", typeof(Sprite)) as Sprite;
                break;

        }
    }
}
