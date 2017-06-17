class Test{
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
	public static void main(String[] args){
		float f1 = 10.0f;
		float f2 = 5.0f;
		Object o = new Object();
		int result = (int)(f1 / f2);
		System.out.println(result);
	}
}
