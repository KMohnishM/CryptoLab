import java.security.MessageDigest;
import java.nio.charset.StandardCharsets;
import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;

public class Main extends JPanel {

    static ArrayList<Integer> sizesList = new ArrayList<>();
    static ArrayList<Long> md5Times = new ArrayList<>();
    static ArrayList<Long> shaTimes = new ArrayList<>();

    public static String toHex(byte[] hash) {
        StringBuilder sb = new StringBuilder();
        for (byte b : hash)
            sb.append(String.format("%02x", b));
        return sb.toString();
    }

    public static void main(String[] args) throws Exception {
        String key = "key12345";
        int[] sizes = {128, 512, 1024, 4096, 8192};

        int i = 0;
        for (int size : sizes) {
            i++;
            String message = "A".repeat(size);
            String combined = key + message;

            // MD5 Hashing
            MessageDigest md5 = MessageDigest.getInstance("MD5");
            long start1 = System.nanoTime();
            byte[] md5Hash = md5.digest(combined.getBytes(StandardCharsets.UTF_8));
            long end1 = System.nanoTime();
            long md5Time = end1 - start1;

            // SHA-512 Hashing
            MessageDigest sha512 = MessageDigest.getInstance("SHA-512");
            long start2 = System.nanoTime();
            byte[] shaHash = sha512.digest(combined.getBytes(StandardCharsets.UTF_8));
            long end2 = System.nanoTime();
            long shaTime = end2 - start2;

            sizesList.add(size);
            md5Times.add(md5Time);
            shaTimes.add(shaTime);

            if (size == 128) {
                System.out.println("\nSample MAC Output (Size 128 bytes):");
                System.out.println("MD5 MAC: " + toHex(md5Hash));
                System.out.println("SHA-512 MAC: " + toHex(shaHash));
                System.out.println("---------------------------------------------------");
            }

            if (i == 1) {
                System.out.println("Size(Bytes)\tMD5(ns)\t\tSHA-512(ns)");
                System.out.println("---------------------------------------------------");
            }
            System.out.println(size + "\t\t" + md5Time + "\t\t" + shaTime);
        }

        JFrame frame = new JFrame("MD5 vs SHA-512 Performance");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(700, 500);
        frame.add(new Main());
        frame.setVisible(true);
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2 = (Graphics2D) g;
        g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

        int width = getWidth();
        int height = getHeight();
        int padding = 60;

        // Draw Axes
        g2.drawLine(padding, height - padding, width - padding, height - padding);
        g2.drawLine(padding, padding, padding, height - padding);

        g2.drawString("Message Size (Bytes)", width / 2 - 50, height - 20);
        g2.drawString("Time (ns)", 10, height / 2);

        long maxTime = Math.max(
                md5Times.stream().max(Long::compare).orElse(1L),
                shaTimes.stream().max(Long::compare).orElse(1L)
        );

        int xGap = (width - 2 * padding) / Math.max(1, sizesList.size() - 1);

        // Plot MD5 (Blue)
        g2.setColor(Color.BLUE);
        for (int j = 0; j < sizesList.size() - 1; j++) {
            int x1 = padding + j * xGap;
            int y1 = height - padding - (int) ((md5Times.get(j) * (height - 2 * padding)) / maxTime);
            int x2 = padding + (j + 1) * xGap;
            int y2 = height - padding - (int) ((md5Times.get(j + 1) * (height - 2 * padding)) / maxTime);

            g2.drawLine(x1, y1, x2, y2);
            g2.fillOval(x1 - 3, y1 - 3, 6, 6);
        }

        // Plot SHA-512 (Red)
        g2.setColor(Color.RED);
        for (int j = 0; j < sizesList.size() - 1; j++) {
            int x1 = padding + j * xGap;
            int y1 = height - padding - (int) ((shaTimes.get(j) * (height - 2 * padding)) / maxTime);
            int x2 = padding + (j + 1) * xGap;
            int y2 = height - padding - (int) ((shaTimes.get(j + 1) * (height - 2 * padding)) / maxTime);

            g2.drawLine(x1, y1, x2, y2);
            g2.fillOval(x1 - 3, y1 - 3, 6, 6);
        }

        // Legend
        g2.setColor(Color.BLUE);
        g2.drawString("MD5", width - 120, padding);
        g2.setColor(Color.RED);
        g2.drawString("SHA-512", width - 120, padding + 20);
    }
}