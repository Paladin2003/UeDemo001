# UeDemo001
Unreal Demo001

此项目为虚幻5的学习项目,虚幻版本：5.2.1
此项目是将B站上面一个初学蓝图教程项目改为C++项目
对应的蓝图教程地址：https://www.bilibili.com/video/BV1Du411h7qe?p=1&vd_source=fe68c73d36d566243a8d4565d558002e

此项目仅包含了核心文件，下载项目后需先编译虚幻项目工程文件.uproject，生成必要的工程文件后，即可运行。



时间轴的绑定：

  1.定义时间轴
    FTimeLine TimeLine;
  
  2.定义曲线
    UPROPERTY(BlueprintReadWrite,EditAnywhere)
  	UCurveFloat* FloatCurve;
  
  3.定义时间轴事件
    //时间轴更新事件，每帧触发
    FOnTimelineFloatStatic OnTimeLineTickCallBack;
    //时间轴完成事件，播放完毕时触发
    FOnTimelineEventStatic OnTimelineFinishedCallBack;
    
  4.定义事件触发后需执行的方法
    UFUNCTION()
	  void OnTimeLineTickFunc();
    UFUNCTION()
	  void OnTimeLineFinishedFunc();
    
  5.在开始中绑定时间轴事件
   void AMyActorA::BeginPlay()
   {
	    //绑定触发更新事件时的方法
	    OnTimeLineTickCallBack.BindUFunction(this,TEXT("OnTimeLineTickFunc"));
      //完成时的方法
      OnTimelineFinishedCallBack.BindUFunction(this,TEXT("OnTimeLineFinishedFunc"));
	    //绑定时间轴的曲线
	    TimeLine.AddInterpFloat(FloatCurve,OnTimeLineTickCallBack);
    }

    6.执行方法逻辑
    void MyActor::OnTimeLineTickFunc()
    {
      //获取时间轴当前的值
      float FloatCurveVal= FloatCurve->GetFloatValue(TimeLine.GetPlaybackPosition());
      ....
    }
