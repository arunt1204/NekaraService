

public class NekaraServiceJava {
	static {
		System.loadLibrary("NekaraService");
	}
	
	public native void NSJ_WithoutSeed();
	public native void NSJ_WithSeed(int _seed);
	public native void NSJ_CreateThread();
	public native void NSJ_StartThread(int _threadID);
	public native void NSJ_EndThread(int _threadID);
	public native void NSJ_ContextSwitch();
	public native void NSJ_WaitforMainTask();
	
	public void CreateThread()
	{
		NSJ_CreateThread();
	}
	
	public void NekaraService()
	{
		NSJ_WithoutSeed();
	}
	
	public void NekaraService(int _seed)
	{
		NSJ_WithSeed(_seed);
	}
	
	public void StartThread(int _threadID)
	{
		NSJ_StartThread(_threadID);
	}
	
	public void EndThread(int _threadID)
	{
		NSJ_EndThread(_threadID);
	}
	
	public void ContextSwitch()
	{
		NSJ_ContextSwitch();
	}
	
	public void WaitforMainTask()
	{
		NSJ_WaitforMainTask();
	}
}
