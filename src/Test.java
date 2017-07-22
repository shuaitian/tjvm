class Test{
	/*
	private Object obj;
	private Integer i;
	private Double d;
	private float f;
	private static Object lock;
	private static int ii;
	private static final int constValue = 1000;
	private static final int constValue02 = 30000;
	private static final long constLong = 4545454545L;
	private static final double constDouble = 43.645342;
	private static final float constFloat = 12.3456F;
	private static final long constLong1 = Long.MAX_VALUE;
	private static final String str = "Hello World";
	*/
	public static int staticVar;
	public int field;
	public static void main(String[] args){
		Test test = new Test();
		test.field = 100;
		int field ;
		field = test.field;
		int sum = 0;
		for(int i=1; i <=100; i++){
			sum+=i;
		}
	}
	/*
	static class Holder
	{
		public static int staticVar;
		public double d = 10.0;
	}
	*/
}
