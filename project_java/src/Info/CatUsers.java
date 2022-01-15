package Info;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.Serializable;
import java.util.HashMap;
import java.util.TreeMap;


public class CatUsers implements Serializable, ICatUsers {
    private HashMap<Character,  TreeMap<String,User>> catalogo;
    private String ficheiro;
    private int numeroTotalUsers;
    private int usersAtivos;


    public CatUsers(HashMap<Character,  TreeMap<String,User>>  catalogo, String ficheiro, int numeroTotalBusinesses, int numeroTotalUsers, int businessesAvaliados, int usersAtivos) {
        this.catalogo = catalogo;
        this.ficheiro = ficheiro;
        this.numeroTotalUsers = numeroTotalUsers;
        this.usersAtivos = usersAtivos;
    }

    public CatUsers() {
        this.catalogo = new HashMap<Character,  TreeMap<String,User>> ();
        this.ficheiro = "";
        this.numeroTotalUsers = 0;
        this.usersAtivos = 0;
    }

    public HashMap<Character,  TreeMap<String,User>> getCatalogo() {
        return this.catalogo;
    }

    public void setCatalogo(HashMap<Character,  TreeMap<String,User>>  catalogo) {
        this.catalogo = catalogo;
    }

    public String getFicheiro() {
        return ficheiro;
    }

    public void setFicheiro(String ficheiro) {
        this.ficheiro = ficheiro;
    }

    public int getNumeroTotalUsers() {
        return numeroTotalUsers;
    }

    public void setNumeroTotalUsers(int numeroTotalUsers) {
        this.numeroTotalUsers = numeroTotalUsers;
    }

    public int getUsersAtivos() {
        return usersAtivos;
    }

    public void setUsersAtivos(int usersAtivos) {
        this.usersAtivos = usersAtivos;
    }

    public void putU(String key, User user){
        
        if(!this.catalogo.containsKey(key.charAt(0))){
            TreeMap<String,User> map = new TreeMap<> ();
            map.put(key,user);
            this.catalogo.put(key.charAt(0),map);
        }
        else{
            this.catalogo.get(key.charAt(0)).put(key, user);
        }



    }

    public void parseUsers(String path, String div) throws FileNotFoundException {

        BufferedReader br = null;
        String line;
        try {
            br = new BufferedReader(new FileReader(path));
            br.readLine();
            while ((line = br.readLine()) != null) {

                User mano = new User();
                String [] buffer = line.split(div);
                if(buffer.length == 3) {
                    mano.setId(buffer[0]);
                    mano.setName(buffer[1]);
                    this.putU(buffer[0], mano);
                    this.numeroTotalUsers++;
                }
            }
            br.close();

        } catch (FileNotFoundException e) {
            System.out.println("Nao ha ficheiro\n");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    public boolean exist(String id){
        if(this.catalogo.get(id.charAt(0))!= null){
        return this.catalogo.get(id.charAt(0)).containsKey(id);
        }
        else{return false;}
    }
}
