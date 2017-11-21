using System.Collections;
using System.Collections.Generic;
using UnityEngine;



public class EffectSound : MonoBehaviour
{
    private AudioSource hsAudio;
    public AudioClip EffectSource1, EffectSource2, EffectSource3, EffectSource4;

    public bool Switch;     // 음향 재생 스위치
    public int SoundSpeed; // 음량 총 재생걸리는 시간
    public int Intiger;     // 추가 조작 변수

    enum State
    {
        State_1,
        State_2,
        State_3,
        State_4
    }

    State CurrentState;

    // Use this for initialization
    void Start()
    {
        Switch = false;
        this.hsAudio = this.gameObject.AddComponent<AudioSource>();
        this.hsAudio.loop = false;
    }
	
	// Update is called once per frame
	void Update () {
	
        if(Switch==true)
        {
            switch (CurrentState)
            {
                case State.State_1:
                    this.hsAudio.PlayOneShot(EffectSource1);
                    break;

                case State.State_2:
                    this.hsAudio.PlayOneShot(EffectSource2);
                    break;

                case State.State_3:
                    this.hsAudio.PlayOneShot(EffectSource3);
                    break;

                case State.State_4:
                    this.hsAudio.PlayOneShot(EffectSource4);
                    break;
            }
        }	
	}
}
