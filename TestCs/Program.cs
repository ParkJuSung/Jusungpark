using System;

namespace testC_
{
    class Program
    {
        static void Main(string[] args)
        {
            List mylist = new List();
            List plist = mylist;

            mylist.ListInsert(plist, 2);
            mylist.ListInsert(plist, 2);
            mylist.ListInsert(plist, 2);
            mylist.ListInsert(plist, 4);
            mylist.ListInsert(plist, 2);


            mylist.ListFirst(plist );
            mylist.ListRemoveAll(plist, 2);
            mylist.ListFirst(plist);
            while (mylist.ListNext(plist, 1)) ;
        }
    }
    public class Node
    {
        public int data;
        public Node Next;
    }

    public class List
    {
        public Node head; //머리
        public Node tail; //꼬리
        public Node cur; //위치
        public Node before; //삭제
        public void ListInsert(List plist, int data)
        {
            Node pnode = null;
            pnode = new Node();
            pnode.data = data;
            pnode.Next = null;

            if (plist.head == null)
            {
                plist.head = pnode;
                plist.tail = pnode;
            }
            else
            {
                plist.tail.Next = pnode;
                plist.tail = pnode;
            }

            return;
        }

        public bool ListRemoveAll(List plist, int data)
        {
            if (plist.head == null)
            {
                return false;
            }

            while (plist.cur != null)
            {
                if (plist.head.Next == null && plist.head.data == data)
                {
                    plist.head = null;
                    plist.tail = null;
                    plist.cur = null;
                    plist.before = null;
                    return true;
                }
                else
                {
                    if (plist.cur != plist.head && plist.cur != plist.tail && plist.cur.data == data)
                    {
                        plist.before.Next = plist.cur.Next;
                        plist.cur = plist.before;
                    }
                    else if (plist.cur == plist.head && plist.cur != plist.tail && plist.cur.data == data)
                    {
                        plist.head = plist.cur.Next;
                        plist.cur = plist.head;
                    }
                    else if (plist.cur != plist.head && plist.cur == plist.tail && plist.cur.data == data)
                    {
                        plist.tail = plist.before;
                        plist.tail.Next = null;
                        plist.cur = plist.tail;
                    }
                    else
                    {
                        plist.before = plist.cur;
                        plist.cur = plist.cur.Next;
                    }
                }
            }
            return true;
        }
        public bool ListRemove(List plist,int data)
        {
            if (plist.head == null)
            {
                Console.WriteLine("List is empty");
                return false;
            }
            if (plist.head.Next == null && plist.head.data == data)
            {
                plist.head = null;
                plist.tail = null;
                plist.cur = null;
                plist.before = null;
                return true;
            }
            else
            {
                if (plist.cur != plist.head && plist.cur != plist.tail && plist.cur.data == data)
                {
                    plist.before.Next = plist.cur.Next;
                    plist.cur = plist.before;
                    return true;
                }
                else if (plist.cur == plist.head && plist.cur != plist.tail && plist.cur.data == data)
                {
                    plist.head = plist.cur.Next;
                    plist.cur = plist.head;
                    return true;
                }
                else if (plist.cur != plist.head && plist.cur == plist.tail && plist.cur.data == data)
                {
                    plist.tail = plist.before;
                    plist.tail.Next = null;
                    plist.cur = plist.tail;
                    return true;
                }
                else
                {
                    plist.before = plist.cur;
                    plist.cur = plist.cur.Next; 
                    if (plist.cur == null)
                    {
                        return true;
                    }
                    return false;
                }
            }
        }

       public bool ListNext(List plist, int print)
        {
            // 현재 cur 포인터가 가리키는 데이터의 옆에 데이터가 없다면
            if (plist.head == null)		// 즉, cur 포인터가 가리키는 노드가 tail 이라면
            {
                return false;
            }
            if (plist.cur == plist.head)
                Console.WriteLine("{0}", plist.cur.data);
            // 현재 cur 포인터가 가리키는 데이터의 옆에 데이터가 있다면 (즉, tail이 아니라면)

            if (plist.cur.Next == null)
            {
                return false;
            }
            plist.before = plist.cur;
            plist.cur = plist.cur.Next;
            if (print == 1)
                Console.WriteLine("{0}", plist.cur.data);
            return true;
        }

        public bool ListFirst(List plist)
        {
            if (plist.head == null)
            {
                Console.WriteLine("List is empty");
                return false;
            }
            plist.before = null;
            plist.cur = plist.head;
            return true;
        }

        public int numOfData(List plist)
        {
            int count = 0;
            if (plist.head != null && plist.tail != null)
            {
                count++;
                while (ListNext(plist, 0))
                    count++;
            }
            return count;
        }
    }
}
