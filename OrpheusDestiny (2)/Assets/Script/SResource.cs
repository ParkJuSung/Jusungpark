using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SResource
{

private static SResource instance = null;
    public static SResource Instance
    {
        get
        {
            if (instance == null)
                instance = new SResource();

            return instance;
        }
    }
private SResource()
    {

    }



    ///// 자원 유아이
    public int GOLD;
    public int FOOD;
    public int IRON;
    public int SOUL; // 영웅의 영혼

    public int Human; // 휴먼 변수
    public int UI_HUMAN;

    ////// 
    public int LEVEL = 1; // 영지 레벨
    public int PEACE = 90; // 만족도
    public int ORDER = 50; // 치안
    public int TAX;   // 세금
    public int COST;  // 나가는 비용
    public int YEAR;
    public int DAY;

    /////// 건물 총 개수
    public int Count_Farm =1;
    public int Count_Bar = 1;
    public int Count_Forge = 1;
    public int Count_Guardner = 1;
    public int Count_Mine = 1;
    public int Count_Trade = 1;
    public int Count_Stable = 1;
    public int Count_Starategy = 1;
    public int Count_Unique = 0;
    //////////////////////////////////////////////////////////////////
    /// </summary>

    public void SetUser()
    {

     GOLD =0;
     FOOD = 0;
     IRON = 0;

     Human = 2500;
    }

}
