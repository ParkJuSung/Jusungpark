using System.Collections;
using System.Collections.Generic;
using UnityEngine.SceneManagement; 
using UnityEngine;

public class SceneSwitch : MonoBehaviour {

    public void MenuScene()
    {
        SceneManager.LoadScene("3MenuScene"); //MenuScene 이동
    }

    public void BattleScene()
    {
        SceneManager.LoadScene("7BattleScene"); // BattleScene 이동
    }

    public void HeroScene()
    {
        SceneManager.LoadScene("4HeroScene"); // HeroScene 이동
    }

    public void ShopScene()
    {
        SceneManager.LoadScene("4ShopScene"); // ShopScene 이동
    }

    public void WorldScene()
    {
        SceneManager.LoadScene("4WorldScene"); //WorldScene 이동
    }

    public void ConQuestScene()
    {
        SceneManager.LoadScene("5ConquestScene"); //Conquest 이동
    }

    public void SetScene()
    {
        SceneManager.LoadScene("6SetScene");
    }

}
