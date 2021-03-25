<template>
<v-alert
  type="success"
>
Comming soon! +7 (978) 89 86 431 Электротовары оптом
<NuxtLink to="/catalog">Catalog</NuxtLink>
  <ul>
    <li v-for="currency of currencies" :key="currency.id">
      <h1>{{ currency.id }} {{ currency.rateBuy }} / {{ currency.rateSell }}</h1>
    </li>
  </ul>
</v-alert>
</template>
<script>
export default {
  async asyncData({ params, $http, $fire }) {
    //const users = await $http.$get(`https://jsonplaceholder.typicode.com/users`);
    const snapshot = await $fire.firestore.collection('currencies').get();
    const currencies = snapshot.docs.map( doc => {
      return {id: doc.id, ...doc.data()}
    });
    return { currencies }
  }
}
</script>
