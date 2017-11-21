using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bgm : MonoBehaviour
{
    private AudioSource hsAudio;
    public AudioClip BGMSource;

    public bool Switch;     // 음향 재생 스위치
    public int SoundSpeed; // 음량 총 재생걸리는 시간
    public int Intiger;     // 추가 조작 변수

    // Use this for initialization
    void Start () {

        Switch = true;

        this.hsAudio = this.gameObject.AddComponent<AudioSource>();
        this.hsAudio.clip = this.BGMSource;
        this.hsAudio.loop = true;

    }
	
	// Update is called once per frame
	void Update () {
		
	}
}
