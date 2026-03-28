import java.security.MessageDigest;
import java.nio.charset.StandardCharsets;

public class md5_sha512 {

    public static String toHex(byte[] hash) {
        StringBuilder sb = new StringBuilder();
        for (byte b : hash) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }

    public static String getMD5(String message) throws Exception {
        MessageDigest md = MessageDigest.getInstance("MD5");
        byte[] hash = md.digest(message.getBytes(StandardCharsets.UTF_8));
        return toHex(hash);
    }

    public static String getSHA512(String message) throws Exception {
        MessageDigest sha = MessageDigest.getInstance("SHA-512");
        byte[] hash = sha.digest(message.getBytes(StandardCharsets.UTF_8));
        return toHex(hash);
    }

    public static void main(String[] args) throws Exception {
        String message = "HelloWorld";

        String md5 = getMD5(message);
        String sha512 = getSHA512(message);

        System.out.println("Message: " + message);
        System.out.println("MD5: " + md5);
        System.out.println("SHA-512: " + sha512);
    }
}