using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BFSConsole : MonoBehaviour {

    BTreeNode[] bt1 = new BTreeNode[9];

    // Use this for initialization
    void Start () {
        for (int i = 0; i < 9; i++)
            bt1[i] = new BTreeNode();

        bt1[0].SetData(0);
        bt1[1].SetData(1);
        bt1[2].SetData(2);
        bt1[3].SetData(3);
        bt1[4].SetData(4);
        bt1[5].SetData(5);
        bt1[6].SetData(6);
        bt1[7].SetData(7);
        bt1[8].SetData(8);

        bt1[0].SetLeftSubTree(bt1[1]);
        bt1[0].SetRightSubTree(bt1[2]);
        bt1[1].SetLeftSubTree(bt1[3]);
        bt1[1].SetRightSubTree(bt1[4]);
        bt1[2].SetRightSubTree(bt1[5]);
        bt1[2].SetLeftSubTree(bt1[6]);
        bt1[3].SetLeftSubTree(bt1[7]);
        bt1[7].SetRightSubTree(bt1[8]);

        bt1[0].BFS();
    }
	
	// Update is called once per frame
	void Update () {
		
	}

    public class BTreeNode
    {
        private int data;
        private BTreeNode left;
        private BTreeNode right;

        public int GetData()
        {
            return data;
        }

        public void SetData(int data)
        {
            this.data = data;
        }

        public BTreeNode GetLeftSubTree()
        {
            return this.left;
        }

        public BTreeNode GetRightSubTree()
        {
            return this.right;
        }

        public void SetLeftSubTree(BTreeNode sub)
        {
            this.left = sub;
        }

        public void SetRightSubTree(BTreeNode sub)
        {
            this.right = sub;
        }

        public void BFS()
        {
            LQueue que = new LQueue();
            BTreeNode tempbt = new BTreeNode();
            tempbt = this;
            que.Enqueue(tempbt);
            while (tempbt != null)
            {
                if (tempbt.left != null)
                    que.Enqueue(tempbt.left);

                if (tempbt.right != null)
                    que.Enqueue(tempbt.right);

                print(tempbt.data);
                tempbt = que.Dequeue();
            }
        }
    }

    public class QueueNode
    {
        private BTreeNode data;
        private QueueNode next;

        public BTreeNode GetData()
        {
            return data;
        }

        public QueueNode GetNext()
        {
            return next;
        }

        public void SetNext(QueueNode next)
        {
            this.next = next;
        }

        public void SetData(BTreeNode data)
        {
            this.data = data;
        }
    }

    public class LQueue
    {
        private QueueNode front;
        private QueueNode rear;

        public bool QIsEmpty(LQueue pq)
        {
            if (pq.front == null)
                return true;
            else
                return false;
        }

        public void Enqueue(BTreeNode data)
        {
            QueueNode newNode = new QueueNode();
            newNode.SetNext(null);
            newNode.SetData(data);

            if (QIsEmpty(this))
            {
                front = newNode;
                rear = newNode;
            }
            else
            {
                rear.SetNext(newNode);
                rear = newNode;
            }
        }

        public BTreeNode Dequeue()
        {
            QueueNode delNode = new QueueNode();
            BTreeNode retData = new BTreeNode();
            if (QIsEmpty(this))
            {
                print("Queue Memory Error");
                return null;
            }

            if (front.GetNext() != null)
            {
                front = front.GetNext();
                delNode = front;
                retData = delNode.GetData();
                return retData;
            }
            else
                return null;
        }
    }
}
