public class Point2D {
    private int x;
    private int y;

    public Point2D(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public int getX() {
        return this.x;
    }

    public int getY() {
        return this.y;
    }

    public static void main(String[] args) {
        Point2D pointOne = new Point2D(10, 100);
        System.out.println("Point coordinates: (" + pointOne.getX() + ", " + pointOne.getY() + ")");
    }
}
