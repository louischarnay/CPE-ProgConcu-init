#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>


typedef struct Thread_param {
    int thread_number;
    int nb_threads;
} Thread_param;

const int size = 3000;

unsigned char *image;

static void calcul(int x, int y, unsigned char *pixel){
  long double p_x = (long double)x/size * 2.0l - 1.0l;
  long double p_y = (long double)y/size * 2.0l - 1.0l;
  long double tz = 0.7;
  long double zoo = powl(0.5l, 13.0l * tz);
  long double cc_x = -0.05l + p_x * zoo;
  long double cc_y = 0.6805l + p_y * zoo;
  long double z_x = 0.0l;
  long double z_y = 0.0l;
  long double m2 = 0.0l;
  long double co = 0.0l;
  long double dz_x = 0.0l;
  long double dz_y = 0.0l;
  int i;
  for (i = 0; i < 2560; i++)
  {
    long double old_dz_x, old_z_x;
    if (m2 > 1024.0l)
      continue;
    // Z' -> 2�Z�Z' + 1
    old_dz_x = dz_x;
    dz_x = 2.0l * z_x * dz_x - z_y * dz_y + 1.0l;
    dz_y = 2.0l * z_x * dz_y + z_y * old_dz_x;
    // Z -> Z� + c
    old_z_x = z_x;
    z_x = cc_x + z_x * z_x - z_y * z_y;
    z_y = cc_y + 2.0l * old_z_x * z_y;
    m2 = z_x * z_x + z_y * z_y;
    co += 1.0l;
  }
  // distance	
  // d(c) = |Z|�log|Z|/|Z'|
  long double d = 0.0l;
  if (co < 2560.0l)
  {
    long double dot_z = z_x * z_x + z_y * z_y;
    d = sqrtl(dot_z/(dz_x*dz_x+dz_y*dz_y)) * logl(dot_z);
    pixel[0] = fmodl(co,256.0l);
    d = 4.0l * d / zoo;
    if (d < 0.0l) d = 0.0l;
    if (d > 1.0l) d = 1.0l;
    pixel[1] = fmodl((1.0l-d) * 255.0l * 300.0l, 255.0l);
    d = powl(d, 50.0l*0.25l);
    pixel[2] = d * 255.0l;
  }
  else
    pixel[0]=pixel[1]=pixel[2]=0;
}

void* thread_function(void* param) {
    Thread_param* thread_param = param;
    //calcul(thread_param->x, thread_param->y, thread_param->pixel);
    int surplus = 0;
    if (thread_param->thread_number+1 == thread_param->nb_threads) {
        surplus = size%thread_param->nb_threads;
    }
    int x,y;
    for (y = (size%thread_param->nb_threads)*thread_param->thread_number; y < (size/thread_param->nb_threads)*(thread_param->thread_number+1) - 1 + surplus; y++)
        for (x = 0; x < size; x++)  {
            //printf("%d\n", 3*(y * size + x));
            calcul(x, y, image+3*(y * size + x));
        }
    
    return NULL;
} 

int main(int argc, char const *argv[])
{
  FILE *file;
  //int x, y;

    int nb_threads = 0;

    if (argc != 2 || sscanf(argv[1], "%d", &nb_threads) == EOF) {
        puts("Invalid number of arguments.");
        exit(-1);
    }

    pthread_t* threads = malloc(nb_threads * sizeof(pthread_t));

    image = malloc(3*size*size);

    for (int i = 0; i < nb_threads; i++) {
        Thread_param param = {i, nb_threads};
        pthread_create(&threads[i], NULL, thread_function, &param);
    }
      
    for (int i = 0; i < nb_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    free(threads);

  // �criture fichier
  file = fopen("image.ppm", "w");
  fprintf(file, "P6\n%d %d\n255\n", size, size);
  fwrite(image, size, size * 3, file);
  fclose(file);
  free(image);

  return 0;
}
