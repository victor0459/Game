using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class lesson7 : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        /*
        //transform主要是用来干嘛的？
        //游戏对象GameObject位移 旋转 缩放 父子关系 坐标转换等相关操作
        //它是unity提供的及其重要的类
        //知识点一 vector基础
        //vector3主要是用来表示三维坐标系中的一个点 或者一个向量
        //声明
        Vector3 v = new Vector3();
        v.x = 10;
        v.y = 10;
        v.z = 10;

        Vector3 v2= new Vector3(10,10);

        Vector3 v3= new Vector3(10,10,10);//常用

        //基本计算
        Vector3 v4= new Vector3(1,1,1);
        Vector3 v5 = new Vector3(2,2,2);
        print(v4 + v5);//3 3 3  就是xyz进行计算
        //常用的几个点
        print(Vector3.zero);//000
        print(Vector3.right);//100
        print(Vector3.left);//-100
        print(Vector3.back);//001
        print(Vector3.forward);//00-1
        print(Vector3.up);//010
        print(Vector3.down);//0-10

        //计算两个点之间距离的方法
        print(Vector3.Distance(v4, v5));
        //--------------------------------------------------------
        //知识点二
        //1 相对世界坐标系
        //this.gameObject.transform
        //通过postion得到的位置是相对于世界坐标系原点的位置
        //可能和面板上显示不一样
        //因为如果对象有父子关系 并且父对象位置 不在原点 那么和面板上肯定就是不一样
        print(this.transform.position);
        //2 相对于父对象的坐标
        //这两个坐标 对于我们来说 很重要 如果你想以面板坐标为准来进行位置设置
        //一定是通过localpostion来进行设置
        print(this.transform.localPosition);
        //3 上面两个会出现一样的情况
        //父对象为原点或者没有父对象

        //注意：位置的复制不能改变xyz 只能整体改变
        //this.transform.position.x = 10; 错误
        //不能改变xyz单独某个值
        this.transform.position = new Vector3(10, 10, 10);
        this.transform.localPosition = Vector3.up * 10;
        //如果指向改一个值x y z保持原有坐标一直
        //方式一 如下只改x
        this.transform.position = new Vector3(19, this.transform.position.y, this.transform.position.z);
        //方式二 先取出来 在赋值
        Vector3 vPos = this.transform.localPosition;
        vPos.x = 10;
        this.transform.localPosition = vPos;

        //对象当前的各朝向
        //如果想得到通过transform.出来即可


        //对象当前面朝向
        print(this.transform.forward);
        //对象当前的头顶朝向
        print(this.transform.up);
        */

        //--------------------------------------------------------
        
    }

    // Update is called once per frame
    void Update()
    {
        //知识点三 位移
        //公式：路程=方向*速度*时间
        //两种方式 方式一
        //想要变化的
        //this.transform.position = this.transform.position + this.transform.right * 1 * Time.deltaTime;
        //this.transform.position  += Vector3.right * 1 * Time.deltaTime;//方向很重要 决定往哪走


        //方式二 API
        //参数一 表示位移多少 
        //参数二表示相对坐标系 默认该参数是相对自己坐标系的
        //1相对于世界坐标系的z轴动
        //this.transform.Translate(Vector3.forward * 1 * Time.deltaTime,Space.World);
        //2相对于世界坐标系 自己的面朝向去动
        //this.transform.Translate(this.transform.forward * 1 * Time.deltaTime, Space.World);
        //3相对于世界坐标系下的自己的面朝向向量移动 一定不会这样移动
        this.transform.Translate(Vector3.forward * 1 * Time.deltaTime, Space.Self);
        //4相对于自己的坐标系下的z轴方向移动 时钟朝自己的面朝向移动
        //this.transform.Translate(Vector3.forward * 1 * Time.deltaTime, Space.Self);

    }
}

