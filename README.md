# UeDemo001
Unreal Demo001

此项目为虚幻5的学习项目,虚幻版本：5.2.1
此项目是将B站上面一个初学蓝图教程项目改为C++项目
对应的蓝图教程地址：https://www.bilibili.com/video/BV1Du411h7qe?p=1&vd_source=fe68c73d36d566243a8d4565d558002e

此项目仅包含了核心文件，下载项目后需先编译虚幻项目工程文件.uproject，生成必要的工程文件后，即可运行。



一、UE C++中时间轴的绑定方法：

1.定义时间轴
  	
   	FTimeLine TimeLine;
  
2.定义曲线
    
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
 	UCurveFloat* FloatCurve; 
    
3.定义事件触发后需执行的方法
  
  	UFUNCTION()
	void OnTimeLineTickFunc();
	UFUNCTION()
	void OnTimeLineFinishedFunc();
    
4.在开始中绑定时间轴事件

	void AMyActorA::BeginPlay()
   	{
		
		//定义事件
		//定义时间轴更新事件，每帧触发
		FOnTimelineFloatStatic OnTimeLineTickCallBack;
		//定义时间轴完成事件，播放完毕时触发
		FOnTimelineEventStatic OnTimelineFinishedCallBack;
		
  		//事件与逻辑方法的绑定
		//绑定触发更新事件时的方法
		OnTimeLineTickCallBack.BindUFunction(this,TEXT("OnTimeLineTickFunc"));
		//绑定完成时触发的方法
		OnTimelineFinishedCallBack.BindUFunction(this,TEXT("OnTimeLineFinishedFunc"));
	    
		//事件与时间轴的绑定
		//时间轴更新时使用的曲线绑定
		TimeLine.AddInterpFloat(FloatCurve,OnTimeLineTickCallBack);
		//时间轴结束时的事件绑定
		TimeLine.SetTimelineFinishedFunc(OnTimelineFinishedCallBack);
		TimeLine.SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);
    	}
     
5.在Tick中 设置TimeLine 的 DeltaSeconds

	void AMyActor::Tick(float DeltaSeconds)
	{
		Super::Tick(DeltaSeconds);
		TimeLine.TickTimeline(DeltaSeconds);
 	}

6.执行方法逻辑
	    
	void MyActor::OnTimeLineTickFunc()
	{
		//获取时间轴当前的值
		float FloatCurveVal= FloatCurve->GetFloatValue(TimeLine.GetPlaybackPosition());
		....
	}

7.在需要触发时间轴的地方调用时间轴的播放方法：

	void MyActor::MyFunc()
 	{

		//是否正在正向播放。。。
  		if(FloatCurve && !TimeLine.IsPlaying)
		{
  			
			//正向播放
  			TimeLine.Play();
			//反向播放
			//TimeLine.Reverse();
			//重新从头开始播放
			//TimeLine.PlayFromStart();
			//重新从尾逆向播放
			//TimeLine.ReverseFromEnd();
			//停止播放
			//TimeLine.Stop();
     			.....
		}
 	}
 
二、绑定延时、定时任务
	
 	1.定义定时器

		FTimerHandle TimerHandle;
  
	2.绑定定时器

     		void ADemoBaseCharacter::BeginPlay()
		{
			Super::BeginPlay();
   			//最后参数表示是否循环，false 即延迟效果;ture 循环效果
			GetWorld()->GetTimerManager().SetTimer(TimerHandle,this,&AMyActor::TimerAutoFunc,1.f,true);
		}
  
  	3.定义任务执行方法
   
		UFUNCTION()
		void TimerAutoFunc();
  
  	4.在适当的时机清除任务

   		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
      	
