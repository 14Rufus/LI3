package Info;

import java.io.Serializable;
import java.util.*;

public class StatsMes implements Serializable {
    private int ano;
    private Double[][] tabela;


    public StatsMes(int ano, Double[][] tabela) {
        this.ano = ano;
        this.tabela = tabela;
    }

    public StatsMes() {
        this.ano = 0;
        this.tabela = new Double[13][3];
    }

    public Double[][] getTabela() {
        Double[][] t = new Double[13][3];
        for (int r = 0; r < 13; r++)
            for (int c = 0; c < 3; c++)
                t[r][c] = this.tabela[r][c];
        return t;
    }

    public void setTabela(Double[][] tabela) {
        this.tabela = tabela;
    }

    public int getAno() {
        return ano;
    }

    public void setAno(int ano) {
        this.ano = ano;
    }

    public void preencheTabela(CatReviews r) {
        double nRanual = 0;
        double nStarsAnual = 0;
        TreeSet<String> userDistintosAno = new TreeSet<>();
        for (int mes = 0; mes < 12; mes++) {
            double avg;
            double nTotalReviews = 0;
            double nTotalStars = 0;
            TreeSet<String> userDistintos = new TreeSet<>();
            AbstractMap.SimpleEntry<Integer, Integer> dataRecebida = new AbstractMap.SimpleEntry<>(this.ano, mes);
            for (Map.Entry<String, HashMap<AbstractMap.SimpleEntry<Integer, Integer>, TreeMap<String, List<Review>>>> entry_reviews : r.getCatalogo().entrySet()) {
                if (r.getCatalogo().get(entry_reviews.getKey()).get(dataRecebida) != null) {
                    for (Map.Entry<String, List<Review>> entry_users : r.getCatalogo().get(entry_reviews.getKey()).get(dataRecebida).entrySet()) {
                        nTotalReviews += entry_users.getValue().size();
                        nTotalStars += entry_users.getValue().stream().mapToDouble(Review::getStars).sum();
                        userDistintos.add(entry_users.getKey());
                        userDistintosAno.add(entry_users.getKey());


                    }
                }
            }
            avg = nTotalStars / nTotalReviews;
            nRanual += nTotalReviews;
            nStarsAnual += nTotalStars;
            this.tabela[mes][0] = nTotalReviews;
            this.tabela[mes][1] = avg;
            this.tabela[mes][2] = (double) userDistintos.size();
        }
        this.tabela[12][0] = nRanual;
        this.tabela[12][1] = nStarsAnual/nRanual;
        this.tabela[12][2] = (double) userDistintosAno.size();
    }
}
