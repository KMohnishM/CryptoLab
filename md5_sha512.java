import java.security.MessageDigest;

public class md5_sha512{

    public static String hash(String input, String algorithm) throws Exception {
        MessageDigest md = MessageDigest.getInstance(algorithm);
        byte[] bytes = md.digest(input.getBytes()); // default charset

        StringBuilder hex = new StringBuilder();
        for (byte b : bytes) {
            hex.append(String.format("%02x", b));
        }
        return hex.toString();
    }

    public static void main(String[] args) throws Exception {
        String message = "HelloWorld";

        System.out.println("MD5: " + hash(message, "MD5"));
        System.out.println("SHA-512: " + hash(message, "SHA-512"));
    }
}