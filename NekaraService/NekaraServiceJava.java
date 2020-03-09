

public class NekaraServiceJava {
	static {
		System.loadLibrary("NekaraService");
	}
	
	private native void NSJ_WithoutSeed();
	private native void NSJ_WithSeed(int _seed);
	private native void NSJ_CreateThread();
	private native void NSJ_StartThread(int _threadID);
	private native void NSJ_EndThread(int _threadID);
	private native void NSJ_ContextSwitch();
	private native void NSJ_WaitforMainTask();
	private native void NSJ_CreateResource(int _resourceID);
	private native void NSJ_DeleteResource(int _resourceID);
	private native void NSJ_BlockedOnResource(int _resourceID);
	private native void NSJ_BlockedOnAnyResource(int[] _resourceID, int _size);
	private native void NSJ_SignalUpdatedResource(int _resourceID);
	private native int NSJ_GenerateResourceID();
	private native int NSJ_GenerateThreadTD();
	private native boolean NSJ_CreateNondetBool();
	private native int NSJ_CreateNondetInteger(int _maxvalue);
	private native boolean NSJ_Dispose();
	
	
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
	
	public void CreateResource(int _resourceID)
	{
		NSJ_CreateResource(_resourceID);
	}
	
	public void DeleteResource(int _resourceID)
	{
		NSJ_DeleteResource(_resourceID);
	}
	
	public void BlockedOnResource(int _resourceID)
	{
		NSJ_BlockedOnResource(_resourceID);
	}
	
	public void BlockedOnAnyResource(int[] _resourceID, int _size)
	{
		NSJ_BlockedOnAnyResource(_resourceID, _size);
	}
	
	public void SignalUpdatedResource(int _resourceID)
	{
		NSJ_SignalUpdatedResource(_resourceID);
	}
	
	public int GenerateThreadTD()
	{
		return NSJ_GenerateThreadTD();
	}
	
	public int GenerateResourceID()
	{
		return NSJ_GenerateResourceID();
	}
	
	public boolean CreateNondetBool()
	{
		return NSJ_CreateNondetBool();
	}
	
	public int CreateNondetInteger(int _maxValue)
	{
		return NSJ_CreateNondetInteger(_maxValue);
	}
	
	public boolean Dispose()
	{
		return NSJ_Dispose();
	}
}
