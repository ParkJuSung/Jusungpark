using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine;

public class BuildArchitecture : MonoBehaviour {

    enum Architecture
    {
        Architecture_Farm,      // 농장 : 식량 생산량을 결정
        Architecture_Bar,       // 주점 : 영웅 방문량을 결정
        Architecture_Forge,     // 대장간 : 병사들의 공격력,방어력 높여줌 
        Architecture_Guardner,  // 헌병소 : 만족도,치안점수 결정
        Architecture_Mine,      // 광산 : 철 생산량을 결정
        Architecture_Trade,     // 상점 : 세금을 올려줌
        Architecture_Stable,    // 마굿간 : 기마병 생산 가능케함
        Architecture_Starategy, // 병법연구소 : 영웅 스킬폭 확대, 전체버프, 영웅성장
        Architecture_UniQue,
    }

    public GameObject WindowBuild;

    public Sprite WB_Barn;
    public Sprite WB_Farm;
    public Sprite WB_Forge;
    public Sprite WB_Unique;
    public Sprite WB_Mine;

    private int Temp;
    private float TempTime;

    // Use this for initialization
    void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
        Temp = Random.Range(0,10);
        Temp = Temp % 5;
        TempTime += Time.deltaTime;
        if(TempTime>10f)
            WindowBuild.SetActive(false);
    }

   public void SetImage()
    {
        TempTime = 0;
        Temp = Temp % 5;
        switch (Temp)
        {
            case 3:
                WindowBuild.GetComponent<Image>().sprite = WB_Forge;
                break;
            case 1:
                WindowBuild.GetComponent<Image>().sprite = WB_Barn;
                break;
            case 2:
                WindowBuild.GetComponent<Image>().sprite = WB_Unique;
                break;
            case 0:
                WindowBuild.GetComponent<Image>().sprite = WB_Farm;
                break;
            case 4:
                WindowBuild.GetComponent<Image>().sprite = WB_Mine;
                break;
        }
        WindowBuild.SetActive(true);
    }
    public void Close()
    {
        WindowBuild.SetActive(false);
    }
}
