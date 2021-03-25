<template>
  <v-app>
    <Navbar/>
    <v-main>
      <v-container>
        <nuxt/>
      </v-container>
    </v-main>
    <v-footer app>
      <a href="//absemetov.org.ua">absemetov.org.ua</a>
    </v-footer>
  </v-app>
</template>

<script>
  import Navbar from "@/components/Navbar";
  export default {
    components: {
      Navbar
    }
  }
</script>
