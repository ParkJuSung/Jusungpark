using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
public class Husband : MonoBehaviour
{

    public enum Unit_State
    {
        Find_State,
        Get_State,
    }

    public int Speed = 12;
    public Unit_State Current_State = Unit_State.Find_State;
    public Transform PlayerTr;
    public Transform CubeTr;
    public Cube Cube_distance;
    public bool flag;
    public GameObject Text;
    public GameObject Button;
    // Use this for initialization
    void Start()
    {
        PlayerTr = this.gameObject.GetComponent<Transform>();
        CubeTr = GameObject.FindWithTag("cube").GetComponent<Transform>();

        if (Cube_distance==null)
            Cube_distance = GameObject.FindWithTag("cube").gameObject.GetComponent<Cube>();

        Text.SetActive(false);
        Button.SetActive(false);
        StartCoroutine(State_Look());
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKey(KeyCode.W) == true)
        {
            PlayerTr.transform.Translate(Vector3.forward * Speed * Time.deltaTime);
        }
        else if (Input.GetKey(KeyCode.S) == true)
        {
            PlayerTr.transform.Translate(-Vector3.forward * Speed * Time.deltaTime);
        }
        else if (Input.GetKey(KeyCode.A) == true)
        {
            PlayerTr.transform.Translate(Vector3.left * Speed * Time.deltaTime);
        }
        else if (Input.GetKey(KeyCode.D) == true)
        {
            PlayerTr.transform.Translate(-Vector3.left * Speed * Time.deltaTime);
        }

        if (Input.GetKey(KeyCode.Space) == true)
        {
            Current_State = Unit_State.Get_State;
            flag =  Cube_distance.get();
            if(flag)
            {
                flag = false;
                Destroy(CubeTr.gameObject);
                Text.SetActive(true);
                Button.SetActive(true);
                //CubeTr = GameObject.FindWithTag("cube").GetComponent<Transform>();
                //Cube_distance = GameObject.FindWithTag("cube").gameObject.GetComponent<Cube>();
            }
            StartCoroutine(Get_Time());
        }

    }

    IEnumerator State_Look()
    {
        while (true)
        {
            Debug.Log(Current_State);
            yield return new WaitForSeconds(1.0f);
        }
    }
    IEnumerator Get_Time()
    {
        yield return new WaitForSeconds(3.0f);
        Current_State = Unit_State.Find_State;
    }
    public bool State_identify()
    {
        if (Current_State == Unit_State.Find_State)
            return false;
        return true;
    }
}
