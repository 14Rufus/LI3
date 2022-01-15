package Info;


//import apple.laf.JRSUIUtils.Tree;

import java.io.*;
import java.util.*;

public class CatBusiness implements Serializable,ICatBusiness {

    private HashMap<Character,  TreeMap<String,Business>>  catalogo;

    private String ficheiro;
    private int numeroTotalBusinesses;
    private int businessesAvaliados;

    public CatBusiness() {
        this.catalogo = new HashMap<>(38);
        this.numeroTotalBusinesses = 0;
        this.businessesAvaliados = 0;
        this.ficheiro = "";
    }

    public HashMap<Character,  TreeMap<String,Business>>  getCatalogo() {
        return catalogo;
    }

    public void setCatalogo(HashMap<Character,  TreeMap<String,Business>> catalogo) {
        this.catalogo = catalogo;
    }

    public String getFicheiro() {
        return ficheiro;
    }

    public void setFicheiro(String ficheiro) {
        this.ficheiro = ficheiro;
    }

    public int getNumeroTotalBusinesses() {
        return numeroTotalBusinesses;
    }

    public void setNumeroTotalBusinesses(int numeroTotalBusinesses) {
        this.numeroTotalBusinesses = numeroTotalBusinesses;
    }

    public int getBusinessesAvaliados() {
        return businessesAvaliados;
    }

    public void setBusinessesAvaliados(int businessesAvaliados) {
        this.businessesAvaliados = businessesAvaliados;
    }

    public void putB(String key, Business business){
        
        if(!this.catalogo.containsKey(key.charAt(0))){
            TreeMap<String,Business> map = new TreeMap<> ();
            map.put(key,business);
            this.catalogo.put(key.charAt(0),map);
        }
        else{
            this.catalogo.get(key.charAt(0)).put(key, business);
        }
    }


    public void parseBusiness(String path, String div) throws IOException {
        BufferedReader br = null;
        String line;
        try {
            br = new BufferedReader(new FileReader(path));
            br.readLine();
            while ((line = br.readLine()) != null) {
                Business business = new Business();
                String[] buffer = line.split(div);
                if (buffer.length == 5) {
                    business.setId(buffer[0]);
                    business.setName(buffer[1]);
                    business.setCity(buffer[2]);
                    business.setState(buffer[3]);
                    List<String> categ = new ArrayList<>();
                    String[] b2 = buffer[4].split(",");
                    int n = 0;
                    for (int i = 0; i < b2.length; i++) {
                        categ.add(i, b2[i]);
                        n++;
                    }
                    business.setCategories(categ);
                    business.setNcategories(n);

                    this.putB(business.getId(), business);

                    this.numeroTotalBusinesses++;
                }
            }


        } catch (FileNotFoundException e) {
            throw new FileNotFoundException();
        } catch (IOException e) {
            throw new IOException();
        }

    }

    public boolean exist(String id){
        if(this.catalogo.get(id.charAt(0))!= null){
        return this.catalogo.get(id.charAt(0)).containsKey(id);    }
        else{return false;
        }
    }

}