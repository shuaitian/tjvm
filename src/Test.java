class Test{
	private Object obj;
	private Integer i;
	private Double d;
	private float f;
	private static Object lock;
	private static int ii;

	public static void main(String[] args){
		float f1 = 10.0f;
		float f2 = 5.0f;
		Object o = new Object();
		int result = (int)(f1 / f2);
		System.out.println(result);
	}
}
