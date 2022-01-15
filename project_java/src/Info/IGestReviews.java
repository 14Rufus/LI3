package Info;

import java.io.FileNotFoundException;
import java.io.IOException;

public interface IGestReviews {
    void Controlador() throws IOException;
    void consultas();
    void load() throws IOException;
    void loadDefault() throws IOException, InterruptedException;
    void loadPersonalizado(String pathUsers,String pathBusiness, String pathReviews, String divisor) throws FileNotFoundException;
    void carregaEstado() throws FileNotFoundException, IOException, ClassNotFoundException;
    void guardaEstado() throws FileNotFoundException, IOException;
    void querie1();
    void querie2(int month,int year);
    void querie3(String id_user);
    void querie4(String id_business);
    void querie5(String codUser);
    void querie6(int size);
    void querie7();
    void querie9(String cod_business, int x);

}
